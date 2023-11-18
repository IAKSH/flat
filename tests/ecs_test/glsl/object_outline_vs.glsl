#version 320 es
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 global_view_without_movement;
   mat4 global_sun_lightspace_matrix;
   vec4 global_camera_position;
   float global_gamma;
   int global_enable_point_shadow;
   int global_enable_direct_shadow;
};

layout(std430, binding = 1) buffer InstanceModelMatrix
{
	mat4 model[];
};

uniform float scale;

void main()
{
    gl_Position = global_projection * global_view * model[gl_InstanceID] * vec4(scale * aPos, 1.0);
}