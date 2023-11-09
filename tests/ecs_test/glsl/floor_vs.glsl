#version 320 es
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 viewPos;
out vec3 FragPos;  
out vec3 Normal;
out vec2 TexCoords;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 view_without_movement;
   vec4 global_camera_position;
   float global_gamma;
};

layout(std430, binding = 1) buffer InstanceModelMatrix
{
	mat4 model[];
};

uniform float texcoords_scale;

void main()
{
    TexCoords = texcoords_scale * aTexCoords;
    viewPos = global_camera_position.xyz;
    FragPos = vec3(model[0] * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model[0]))) * aNormal; // 开销较大，考虑在CPU计算后作为uniform传入
    gl_Position = global_projection * global_view * model[0] * vec4(aPos, 1.0);
}