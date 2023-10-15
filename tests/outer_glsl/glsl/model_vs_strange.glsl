#version 320 es
precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 randomVertexOffset(vec3 vertexPosition, vec3 vertexNormal, float delta)
{
    vec3 randomVector = normalize(vec3(rand(vec2(gl_VertexID, 0.0)), 
                                       rand(vec2(gl_VertexID, 1.0)), 
                                       rand(vec2(gl_VertexID, 2.0))));

    vec3 offsetPosition = vertexPosition + delta * randomVector;

    return offsetPosition;
}

void main()
{
    TexCoords = aTexCoords;
    vec3 offsetPosition = randomVertexOffset(aPos, aNormal, 0.5) * randomVertexOffset(aPos, aNormal,1.5);
    gl_Position = projection * view * model * vec4(offsetPosition, 1.0);
}