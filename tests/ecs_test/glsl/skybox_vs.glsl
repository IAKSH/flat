#version 320 es
precision lowp float;

layout (location = 0) in vec3 aPos;

out vec3 texCoord;

uniform mat4 skybox_view;

layout (std140) uniform CameraMatrix
{
   mat4 projection;
   mat4 view;
};

void main()
{
    texCoord = aPos;
    gl_Position = projection * skybox_view * vec4(aPos,1.0);
}