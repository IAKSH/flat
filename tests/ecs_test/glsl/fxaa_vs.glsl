#version 320 es

precision highp float;
precision highp int;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 in_uv;

void main()
{
	in_uv = aTexCoords;
	gl_Position = vec4(aPos, 1.0);
}