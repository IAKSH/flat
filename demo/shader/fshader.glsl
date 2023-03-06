#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture0;

void main()
{
    vec4 texColor = texture(texture0,TexCoord) * vec4(ourColor,1.0f);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}