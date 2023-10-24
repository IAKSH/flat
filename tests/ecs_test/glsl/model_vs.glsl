#version 320 es
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

//uniform mat4 model;

layout (std140) uniform CameraMatrix
{
   mat4 projection;
   mat4 view;
   mat4 view_without_movement;
};

layout(std430, binding = 1) buffer InstanceModelMatrix
{
	mat4 model[];
};

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model[gl_InstanceID] * vec4(aPos, 1.0);
}