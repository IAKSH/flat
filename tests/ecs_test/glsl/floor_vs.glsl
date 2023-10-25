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
   mat4 view_without_movement;
   vec4 global_camera_position;
   float global_gamma;
};

uniform mat4 model;
uniform float texcoords_scale;

void main()
{
    gamma = global_gamma;
    TexCoords = texcoords_scale * aTexCoords;
    viewPos = global_camera_position.xyz;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; // �����ϴ󣬿�����CPU�������Ϊuniform����
    gl_Position = global_projection * global_view * model * vec4(aPos, 1.0);
}