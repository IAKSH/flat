#version 320 es
precision lowp float;

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D tex;

// ����debug view��ʵ����ɫ�����ǿ��Ը��õİɣ���ȫû�в��

void main()
{
    FragColor = texture(tex, texCoords);
}