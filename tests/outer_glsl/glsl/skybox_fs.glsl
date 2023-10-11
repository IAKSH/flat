#version 330 core
out vec4 fragColor;

in vec3 texCoord;

uniform samplerCube skybox_cubemap;

void main()
{
    fragColor = texture(skybox_cubemap,texCoord);
}