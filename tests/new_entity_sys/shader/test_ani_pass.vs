#version 320 es
#extension GL_CPPOES_shader_type_flag : enable
#glsl_type "vertex"

precision highp float;
precision highp int;

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in vec3 in_tangent;
layout(location = 4) in vec3 in_bitangent;
layout(location = 5) in ivec4 in_boneIds; 
layout(location = 6) in vec4 in_weights;

out vec2 uv;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];
uniform mat4 pvm;

void main()
{
	vec4 total_pos = vec4(0.0);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(in_boneIds[i] == -1) 
            continue;
        if(in_boneIds[i] >=MAX_BONES) 
        {
            total_pos = vec4(in_pos,1.0);
            break;
        }
        vec4 local_position = finalBonesMatrices[in_boneIds[i]] * vec4(in_pos,1.0);
        total_pos += local_position * in_weights[i];
        vec3 local_normal = mat3(finalBonesMatrices[in_boneIds[i]]) * in_normal;
   }
	
    gl_Position =  pvm * total_pos;
    //gl_Position = pvm * vec4(in_pos,1.0);
	uv = in_uv;
}