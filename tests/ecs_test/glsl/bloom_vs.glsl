#version 320 es
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

// 这些后处理的vs都一模一样的
// 以后考虑用named string，在ogl里做include吧
// 好像有这种扩展，然后就可以复用代码了

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}