#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 camTrans;

out vec2 aTexCoordOut;

void main()
{
    gl_Position =  camTrans * transform * vec4(aPos, 1.0f);
    aTexCoordOut = vec2(aTexCoord.x - 1.0, 1.0f - aTexCoord.y);
}