#version 320 es
precision mediump float;

out vec4 FragColor;
in vec2 texCoords;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 global_view_without_movement;
   mat4 global_sun_lightspace_matrix;
   vec4 global_camera_position;
   float global_gamma;
   int global_enable_point_shadow;
   int global_enable_direct_shadow;
};

uniform sampler2D sceneTex;
uniform sampler2D bloomTex;
uniform float exposure;
uniform bool enable_exposure;
uniform bool enableBloom;

// hdr, gamma and bloom
vec3 postBlend()
{
    vec3 sceneColor = texture(sceneTex, texCoords).rgb;
    vec3 bloomColor = texture(bloomTex, texCoords).rgb;
    if(enableBloom)
    {
        float sceneColorSum = sceneColor.r + sceneColor.g + sceneColor.b;
        float bloomColorSum = bloomColor.r + bloomColor.g + bloomColor.b;

        sceneColor = sceneColorSum > bloomColorSum ? sceneColor : bloomColor;
    }
        
    vec3 result;
    if(enable_exposure)
    {
        // exposure
        result = vec3(1.0) - exp(-sceneColor * exposure);
    }
    else
    {   
        // reinhard
        result = sceneColor / (sceneColor + vec3(1.0));
    }

    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / global_gamma));

    return result;
}

void main()
{
    FragColor = vec4(postBlend(),1.0);
}