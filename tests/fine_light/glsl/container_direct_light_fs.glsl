#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
}; 

struct DirectLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;  
    vec3 direction;
    float cutOff; 
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
uniform vec3 viewPos;
uniform Material material;
uniform DirectLight directLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

out vec4 FragColor;

vec3 processDirectLight()
{
    // ambient
    vec3 ambient = directLight.ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-directLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = directLight.specular * spec * texture(material.specular, TexCoords).rgb;
    
    return ambient + diffuse + specular;
}

vec3 processPointLight()
{
    // ambient
    vec3 ambient = pointLight.ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(pointLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * spec * texture(material.specular, TexCoords).rgb;

    float distance    = length(pointLight.position - FragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + 
        pointLight.quadratic * (distance * distance));

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 processSpotLight()
{
    vec3 lightDir = normalize(spotLight.position - FragPos);

    float theta = dot(lightDir, normalize(-spotLight.direction));
    if(theta > spotLight.cutOff) 
    {
        // ambient
        vec3 ambient = spotLight.ambient * texture(material.diffuse, TexCoords).rgb;
    
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spotLight.specular * spec * texture(material.specular, TexCoords).rgb;
        
        // attenuation
        float distance    = length(spotLight.position - FragPos);
        float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));    

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
        diffuse   *= attenuation;
        specular *= attenuation;   

        return ambient + diffuse + specular;
    }
    else
        return spotLight.ambient * vec3(texture(material.diffuse, TexCoords));
}

vec3 processSpotLightSoft()
{
    // ambient
    vec3 ambient = spotLight.ambient * texture(material.diffuse, TexCoords).rgb;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(spotLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * spec * texture(material.specular, TexCoords).rgb;  
    
    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-spotLight.direction)); 
    float epsilon = (spotLight.cutOff - spotLight.outerCutOff);
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(spotLight.position - FragPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;  

    return ambient + diffuse + specular;
}

void main()
{
    FragColor = vec4(processSpotLightSoft() + processPointLight() + processDirectLight(), 1.0);
}