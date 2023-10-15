#version 320 es
precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 transposedInversedModel;

out vec3 FragPos;  
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos + vec3(gl_InstanceID % 10,gl_InstanceID % 2,gl_InstanceID % 3), 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = transposedInversedModel * aNormal;
}