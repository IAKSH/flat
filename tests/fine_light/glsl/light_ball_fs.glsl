#version 320 es

in vec3 outLightColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(outLightColor,1.0);
}