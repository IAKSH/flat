#version 330 core

uniform sampler2D texture0; // 纹理采样器

in vec4 aColorOut;    // 文字颜色
in vec2 aTexCoordOut; // 输入的纹理坐标

out vec4 FragColor; // 输出的颜色

void main()
{
    float alpha = texture(texture0, aTexCoordOut).r;
    vec3 grayScale = vec3(alpha);
    
    // 计算最终颜色
    FragColor = vec4(aColorOut.rgb * grayScale, alpha * aColorOut.a);
}