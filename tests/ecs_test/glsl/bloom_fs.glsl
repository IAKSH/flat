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

    // UV��ֵͨ���ǹ�һ����
    // ����ʵ����Ӧ�øĸ�����
    float uv_x = TexCoords.x * size.x;
    float uv_y = TexCoords.y * size.y;

    // 9x9���������ƽ��
    // ��û���ϸ�˹ģ�����ѹִ�����ô��
    // ��Ȼ��1pass�����ǣ�����̫���ˣ�81�β�����Ч�ʲ���ƹ��ʽһά��˹ģ��
    // ����Ч������˵����
    // Ҫ�ĳɸ�˹ģ����ʵҲ�ð�
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
        // ����ӵ���9x9�������ÿ�е�ƽ��
        sum += h_sum / 9.0;
    }

    // ���sum/9.0��ȡ������������ƽ��
    FragColor = texture(image, TexCoords) - ((sum / 9.0) * bloom_intensity);
}
