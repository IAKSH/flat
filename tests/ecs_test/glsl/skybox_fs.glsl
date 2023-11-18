#version 320 es
precision mediump float;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 texCoord;

uniform samplerCube skybox_cubemap;

layout (std140) uniform PhoneDirectLighting
{
    vec4 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

void main()
{
    vec4 result = ambient * texture(skybox_cubemap,texCoord);
    FragColor = result;

    /*
    // 基于NTSC亮度经验公式的亮部提取
    // 提取出的部分用于高斯模糊，形成泛光
    float brightness = dot(result.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    */

    // 提高整体亮度，强化泛光
    // 也许等泛光做了升降采样就不用这个了
    result *= 1.5;

    // 类原神的色彩阈值式亮部提取
    // 相比NTSC亮度经验公式，也许能更好保留色彩饱和度
    // 提取出的部分用于高斯模糊，形成泛光
    const vec3 threshold = vec3(0.5,0.5,0.5); // skybox的阈值比常规obj更低
    BrightColor = vec4(max(result.rgb - threshold,vec3(0.0,0.0,0.0)),1.0);
}