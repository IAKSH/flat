#version 320 es
#extension GL_CPPOES_shader_type_flag : enable
#glsl_type "vertex"

precision highp float;
precision highp int;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
out vec2 uv;
out vec3 color_interp;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(aPos,1.0);
	for(lowp int i = 0;i < 3;i++)
		color_interp[i] = model[i][i];
	uv = aTexCoords;
}