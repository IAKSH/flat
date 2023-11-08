#version 460 core
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out flat int instanceID;
out float gamma;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 view_without_movement;
   vec4 global_camera_position;
   float global_gamma;
};

layout(std430, binding = 5) buffer InstanceModelMatrix
{
	mat4 model[];
};

void main()
{
    instanceID = gl_InstanceID;
    gamma = global_gamma;
    gl_Position = global_projection * global_view * model[gl_InstanceID] * vec4(aPos, 1.0);
}