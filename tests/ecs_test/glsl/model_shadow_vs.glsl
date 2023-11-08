#version 460 core
precision highp float;

layout (location = 0) in vec3 aPos;

layout(std430, binding = 1) buffer InstanceModelMatrix
{
	mat4 model[];
};

void main()
{
    gl_Position = model[gl_InstanceID] * vec4(aPos, 1.0);
}