#version 320 es
#extension GL_CPPOES_shader_type_flag : enable
#glsl_type "fragment"

precision highp float;
precision highp int;

out vec4 frag_color;
in vec2 uv;

uniform sampler2D diffuse;

void main()
{
    frag_color = texture(diffuse,uv);
}