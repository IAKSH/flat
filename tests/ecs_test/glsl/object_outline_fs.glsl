#version 320 es
precision highp float;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

out vec4 fragColor;

void main()
{
    fragColor = vec4(0.0,0.0,0.0,1.0);
}