#version 320 es
precision highp float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

// ��Щ�����vs��һģһ����
// �Ժ�����named string����ogl����include��
// ������������չ��Ȼ��Ϳ��Ը��ô�����

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}