#version 320 es
precision highp float;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in flat int instanceID;

layout(std430, binding = 6) buffer InstanceColor
{
	vec4 color[];
};

void main()
{
    FragColor = color[instanceID];

	float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    // 实际上应该 > 1.0，但是这个demo的光球大多都太暗了
    if(brightness > 0.5)
        BrightColor = vec4(FragColor.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}