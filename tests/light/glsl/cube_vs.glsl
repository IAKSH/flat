#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;  
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));

    // ����������һ�������ɫ�������ܴ�����㣬��Ϊ�������ڳ����е�ÿһ�������Ͻ��У�����Ӧ�þ����ܵر�������ɫ���н����������㡣
    // ��ѧϰΪĿ�ĵĻ����������ã����Ƕ���һ����Ч��Ӧ����˵�����������CPU�ϼ�������߾�����ͨ��uniform�������ݸ���ɫ��������ģ�;���һ������
    Normal = mat3(transpose(inverse(model))) * aNormal;
}