// modified from https://github.com/kiwipxl/GLSL-shaders/blob/master/bloom.glsl

#version 320 es
precision highp float;

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D image;
// temp
const float bloom_spread = 1.0;
const float bloom_intensity = 2.5;

void main()
{
	vec2 size = vec2(textureSize(image, 0));

    // UV的值通常是归一化的
    // 这里实际上应该改个名字
    float uv_x = TexCoords.x * size.x;
    float uv_y = TexCoords.y * size.y;

    // 9x9卷积，滑动平均
    // 并没有上高斯模糊，难怪代码这么少
    // 虽然是1pass，但是，采样太多了，81次采样，效率不如乒乓式一维高斯模糊
    // 至于效果，我说不好
    // 要改成高斯模糊其实也好办
    vec4 sum = vec4(0.0);
    for (int n = 0; n < 9; ++n)
    {
        uv_y = (TexCoords.y * size.y) + (bloom_spread * float(n - 4));
        vec4 h_sum = vec4(0.0);
        h_sum += texelFetch(image, ivec2(uv_x - (4.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x - (3.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x - (2.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x - bloom_spread, uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x, uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x + bloom_spread, uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x + (2.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x + (3.0 * bloom_spread), uv_y), 0);
        h_sum += texelFetch(image, ivec2(uv_x + (4.0 * bloom_spread), uv_y), 0);
        // 这里加的是9x9卷积块中每行的平均
        sum += h_sum / 9.0;
    }

    // 最后sum/9.0是取得整个卷积快的平均
    FragColor = texture(image, TexCoords) - ((sum / 9.0) * bloom_intensity);
}
