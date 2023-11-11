#version 320 es
precision mediump float;

layout (location = 0) in vec3 aPos;

out vec3 texCoord;

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

void main()
{
    texCoord = aPos;
    gl_Position = global_projection * global_view_without_movement * vec4(aPos,1.0);
}