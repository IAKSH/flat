#version 330 core

uniform sampler2D texture0; // 纹理采样器
uniform vec4 textColor;    // 文字颜色
uniform vec4 outlineColor; // 描边颜色
uniform float outlineThickness; // 描边厚度

in vec2 aTexCoordOut; // 输入的纹理坐标

out vec4 FragColor; // 输出的颜色

void main()
{
    float alpha = texture(texture0, aTexCoordOut).r;
    vec3 grayScale = vec3(alpha);
    
    // 计算描边效果
    float distance = length((aTexCoordOut - vec2(0.5)) * (1.0 / fwidth(aTexCoordOut)));
    float border = smoothstep(0.5 - outlineThickness, 0.5 + outlineThickness, distance);
    
    // 计算最终颜色
    vec4 color = mix(outlineColor, textColor, border);
    FragColor = vec4(color.rgb * grayScale, alpha * color.a);
}