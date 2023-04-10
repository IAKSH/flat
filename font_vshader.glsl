#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 camTrans;
out vec4 aColorOut;
out vec2 aTexCoordOut;

void main()
{
    gl_Position =  camTrans * vec4(aPos.xy,0.9f, 1.0f);
    aColorOut = aColor;
    aTexCoordOut = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}