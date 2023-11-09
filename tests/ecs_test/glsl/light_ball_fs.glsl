#version 320 es
precision highp float;

out vec4 FragColor;

in flat int instanceID;

layout(std430, binding = 6) buffer InstanceColor
{
	vec4 color[];
};

void main()
{
    FragColor = color[instanceID];
}