#version 320 es
precision highp float;

layout (location = 0) in vec3 position;

uniform mat4 lightSpaceMatrix;

layout(std430, binding = 1) buffer InstanceModelMatrix
{
	mat4 model[];
};

void main()
{
    gl_Position = lightSpaceMatrix * model[gl_InstanceID] * vec4(position, 1.0f);
}