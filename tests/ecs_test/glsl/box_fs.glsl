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
    float     shininess;
};

uniform Material material;

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
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = phone_direct_lighting_specular.rgb * spec * texture(material.specular, TexCoords).rgb;
    
    return ambient + diffuse + specular;
}

/*
vec3 processPointLight()
{
    vec4 phone_direct_lighting_position = vec4(viewPos,1.0);

    // ambient
    vec3 ambient = phone_direct_lighting_ambient.rgb * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(phone_direct_lighting_position.rgb - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = phone_direct_lighting_diffuse.rgb * diff * texture(material.diffuse, TexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = phone_direct_lighting_specular.rgb * spec * texture(material.specular, TexCoords).rgb;

    float distance    = length(phone_direct_lighting_position.rgb - FragPos);
    float attenuation = 1.0 / (phone_direct_lighting_constant.rgb + phone_direct_lighting_linear.rgb * distance + 
        phone_direct_lighting_quadratic.rgb * (distance * distance));

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}
*/

void main()
{
    //vec3 result = processDirectLight() + processPointLight;
    //FragColor = vec4(result, 1.0);

    vec4 result = vec4(processDirectLight(), 1.0);
    float gamma = 2.2;
    result.rgb = pow(result.rgb, vec3(1.0/gamma));
    FragColor = result;
}