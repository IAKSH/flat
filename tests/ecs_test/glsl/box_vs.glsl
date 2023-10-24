#version 320 es
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 viewPos;
out vec3 FragPos;  
out vec3 Normal;
out vec2 TexCoords;

layout (std140) uniform CameraMatrix
{
   mat4 projection;
   mat4 view;
   mat4 view_without_movement;
   vec4 camera_position;
};

layout(std430, binding = 4) buffer InstanceModelMatrix
{
	mat4 model[];
};

void main()
{
    TexCoords = aTexCoords;
    viewPos = camera_position.xyz;
    FragPos = vec3(model[gl_InstanceID] * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model[gl_InstanceID]))) * aNormal; // 开销较大，考虑在CPU计算后作为uniform传入
    gl_Position = projection * view * model[gl_InstanceID] * vec4(aPos, 1.0);
}