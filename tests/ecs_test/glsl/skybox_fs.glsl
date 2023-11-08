#version 460 core
precision lowp float;

out vec4 FragColor;

in vec3 texCoord;
in float gamma;

uniform samplerCube skybox_cubemap;

layout (std140) uniform PhoneDirectLighting
{
    vec4 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

void main()
{
    vec4 result = ambient * texture(skybox_cubemap,texCoord);
    result.rgb = pow(result.rgb, vec3(1.0/gamma));
    FragColor = result;
}