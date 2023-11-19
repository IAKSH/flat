#version 320 es
precision lowp float;

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D tex;

// 几个debug view其实连着色器都是可以复用的吧，完全没有差别

void main()
{
    FragColor = texture(tex, texCoords);
}