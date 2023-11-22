#version 320 es
#extension GL_CPPOES_shader_type_flag : enable
#glsl_type "vertex"

precision highp float;
precision highp int;

layout (location = 0) in vec3 in_pos;
layout (location = 2) in vec2 in_uv;
out vec2 uv;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(in_pos,1.0);
	uv = in_uv;
}