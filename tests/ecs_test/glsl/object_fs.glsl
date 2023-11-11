#version 320 es
precision highp float;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 viewPos;
in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 global_view_without_movement;
   mat4 global_sun_lightspace_matrix;
   vec4 global_camera_position;
   float global_gamma;
   int global_enable_point_shadow;
   int global_enable_direct_shadow;
};

layout (std140) uniform PhoneDirectLighting
{
    vec4 phone_direct_lighting_direction;
    vec4 phone_direct_lighting_ambient;
    vec4 phone_direct_lighting_diffuse;
    vec4 phone_direct_lighting_specular;
};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D shadow_depth_map;
    samplerCube point_shadow_depth_map;
    float     shininess;
    float texcoords_scale;
}; 

uniform Material material;
uniform bool useBlinnPhong;

layout(std430, binding = 6) buffer LightBallInstanceColor
{
	vec4 lightBallColor[];
};

layout(std430, binding = 5) buffer LightBallInstanceModelMatrix
{
	mat4 lightBallModel[];
};

layout(std430, binding = 7) buffer LightBallInstancePos
{
	vec4 lightBallPos[];
};

layout(std430, binding = 8) buffer LightBallInstanceCount
{
	int lightBallInstance;
};

layout(std430, binding = 9) buffer LightBallAttenuation
{
	float light_ball_constant;
    float light_ball_linear;
	float light_ball_quadratic;
};

// array of offset direction for sampling
vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float PointShadowCalculation(vec3 fragPos)
{
    float far_plane = 25.0;
    vec3 lightPos = -phone_direct_lighting_direction.xyz;

    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);
    
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    //                                                      ↓ 这个magic num与阴影模糊度负相关
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 125.0;
    float closestDepth;
    for(int i = 0; i < samples; ++i)
    {
        closestDepth = texture(material.point_shadow_depth_map, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth > far_plane)
            shadow = 0.0;
        else if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
        
    // display closestDepth as debug (to visualize depth cubemap)
    //FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    return shadow;
}

float DirectShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 lightPos = -phone_direct_lighting_direction.xyz;

    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(material.shadow_depth_map, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(material.shadow_depth_map, 0));
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(material.shadow_depth_map, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

// 没用，但是留着以后可能会用
float DirectShadowCalculation_hard(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(material.shadow_depth_map, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

vec3 processDirectLight()
{
    vec2 scaledTexCoords = material.texcoords_scale * TexCoords;

    // ambient
    vec3 ambient = phone_direct_lighting_ambient.rgb * texture(material.diffuse, scaledTexCoords).rgb;
  
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-phone_direct_lighting_direction.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = phone_direct_lighting_diffuse.rgb * diff * texture(material.diffuse, scaledTexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    float spec;
    if(useBlinnPhong)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), material.shininess);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, Normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    vec3 specular = phone_direct_lighting_specular.rgb * spec * texture(material.specular, scaledTexCoords).rgb;

    // calculate shadow
    float shadow;
    if(global_enable_point_shadow == 1)
        shadow = PointShadowCalculation(FragPos);
    else if(global_enable_direct_shadow == 1)
        shadow = DirectShadowCalculation(global_sun_lightspace_matrix * vec4(FragPos, 1.0));
    else
        shadow = 0.0;

    return ambient + (1.0 - shadow) * (diffuse + specular);
}

vec3 processPointLight(vec3 light_ball_position,vec3 light_ball_ambient,vec3 light_ball_diffuse,vec3 light_ball_specular)
{
    vec2 scaledTexCoords = material.texcoords_scale * TexCoords;

    // ambient
    vec3 ambient = light_ball_ambient * texture(material.diffuse, scaledTexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light_ball_position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light_ball_diffuse * diff * texture(material.diffuse, scaledTexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    float spec;
    if(useBlinnPhong)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), material.shininess);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, Normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    vec3 specular = light_ball_specular * spec * texture(material.specular, scaledTexCoords).rgb;

    // attenuation
    float distance    = length(light_ball_position - FragPos);
    float attenuation = 1.0 / (light_ball_constant + light_ball_linear * distance + 
                light_ball_quadratic * (distance * distance));

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 result = processDirectLight();
    for(int i = 1;i < lightBallInstance;i++)
    {
        result += processPointLight(
            lightBallPos[i].rgb,
            lightBallColor[i].rgb,
            lightBallColor[i].rgb,
            lightBallColor[i].rgb
        );
    }

    FragColor = vec4(result,1.0);
    
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}