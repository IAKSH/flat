#version 320 es
precision lowp float;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 texCoord;

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
    FragColor = result;
    BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}