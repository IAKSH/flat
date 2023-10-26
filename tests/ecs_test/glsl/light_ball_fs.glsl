#version 320 es
precision highp float;

out vec4 FragColor;

in flat int instanceID;
in float gamma;

layout(std430, binding = 6) buffer InstanceColor
{
	vec4 color[];
};

void main()
{
    vec4 result = vec4(pow(color[instanceID].rgb, vec3(1.0/gamma)),1.0);
    FragColor = result;
}