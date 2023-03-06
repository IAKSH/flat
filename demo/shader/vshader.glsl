#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

//uniform vec2 xyoffset;
//uniform vec2 xyoffset_tex;
//uniform mat4 transform;

void main()
{
    //gl_Position = vec4(aPos.x + xyoffset.x,aPos.y + xyoffset.y,aPos.z,1.0);
    //gl_Position = transform * vec4(aPos, 1.0f);
    gl_Position = vec4(aPos, 1.0f);
    ourColor = aColor;
    //TexCoord = vec2(aTexCoord.x + xyoffset_tex.x,aTexCoord.y + xyoffset_tex.y);
    TexCoord = aTexCoord;
}