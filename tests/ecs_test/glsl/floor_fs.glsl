#version 320 es
precision highp float;

out vec4 FragColor;

in vec3 viewPos;
in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords;

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
    samplerCube depth_map;
    float     shininess;
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

float ShadowCalculation(vec3 fragPos)
{
    float far_plane = 100.0;
    vec3 lightPos = -phone_direct_lighting_direction.xyz;

    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);
    
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 125.0;
    float closestDepth;
    for(int i = 0; i < samples; ++i)
    {
        closestDepth = texture(material.depth_map, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= far_plane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);
        
    // display closestDepth as debug (to visualize depth cubemap)
    //FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
        
    return shadow;
}

vec3 processDirectLight()
{
    // ambient
    vec3 ambient = phone_direct_lighting_ambient.rgb * texture(material.diffuse, TexCoords).rgb;
  
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-phone_direct_lighting_direction.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = phone_direct_lighting_diffuse.rgb * diff * texture(material.diffuse, TexCoords).rgb;
    
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
    vec3 specular = phone_direct_lighting_specular.rgb * spec * texture(material.specular, TexCoords).rgb;

    // calculate shadow
    float shadow = ShadowCalculation(FragPos);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));

    return lighting;
}

vec3 processPointLight(vec3 light_ball_position,vec3 light_ball_ambient,vec3 light_ball_diffuse,vec3 light_ball_specular)
{
    // ambient
    vec3 ambient = light_ball_ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light_ball_position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light_ball_diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
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
    vec3 specular = light_ball_specular * spec * texture(material.specular, TexCoords).rgb;

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
}