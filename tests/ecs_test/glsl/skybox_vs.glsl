#version 320 es
precision lowp float;

layout (location = 0) in vec3 aPos;

out vec3 texCoord;

layout (std140) uniform CameraMatrix
{
   mat4 projection;
   mat4 view;
   mat4 view_without_movement;
};

void main()
{
    texCoord = aPos;
    gl_Position = projection * view_without_movement * vec4(aPos,1.0);
}