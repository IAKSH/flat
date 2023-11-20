#version 320 es
#extension GL_CPPOES_shader_type_flag : enable
#glsl_type "fragment"

precision highp float;
precision highp int;

out vec4 frag_color;
in vec2 uv;
in vec3 color_interp;

void main()
{
    frag_color = vec4(uv.x + color_interp.r,uv.x + color_interp.g,uv.y + color_interp.b,uv.y);
}