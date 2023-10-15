#version 320 es
layout (location = 0) in vec3 aPos;
layout (location = 6) in vec3 instanceLightColor;
layout (location = 7) in mat4 instanceModel;

uniform mat4 view;
uniform mat4 projection;
out vec3 outLightColor;

void main()
{
    gl_Position = projection * view * instanceModel * vec4(aPos, 1.0);
    outLightColor = instanceLightColor;
}