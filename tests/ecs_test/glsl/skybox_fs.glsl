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
    // ����NTSC���Ⱦ��鹫ʽ��������ȡ
    // ��ȡ���Ĳ������ڸ�˹ģ�����γɷ���
    float brightness = dot(result.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    */

    // ����������ȣ�ǿ������
    // Ҳ��ȷ����������������Ͳ��������
    result *= 1.5;

    // ��ԭ���ɫ����ֵʽ������ȡ
    // ���NTSC���Ⱦ��鹫ʽ��Ҳ���ܸ��ñ���ɫ�ʱ��Ͷ�
    // ��ȡ���Ĳ������ڸ�˹ģ�����γɷ���
    const vec3 threshold = vec3(0.5,0.5,0.5); // skybox����ֵ�ȳ���obj����
    BrightColor = vec4(max(result.rgb - threshold,vec3(0.0,0.0,0.0)),1.0);
}