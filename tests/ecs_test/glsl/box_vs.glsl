#version 320 es
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 viewPos;
out vec3 FragPos;  
out vec3 Normal;
out vec2 TexCoords;
out float gamma;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 global_view_without_movement;
   vec4 global_camera_position;
   float global_gamma;
};

layout(std430, binding = 4) buffer InstanceModelMatrix
{
	mat4 model[];
};

void main()
{
    gamma = global_gamma;
    TexCoords = aTexCoords;
    viewPos = global_camera_position.xyz;
    FragPos = vec3(model[gl_InstanceID] * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model[gl_InstanceID]))) * aNormal; // 开销较大，考虑在CPU计算后作为uniform传入
    gl_Position = global_projection * global_view * model[gl_InstanceID] * vec4(aPos, 1.0);
}