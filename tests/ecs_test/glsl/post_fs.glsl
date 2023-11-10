#version 430 core
precision highp float;

out vec4 FragColor;
in vec2 texCoords;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 view_without_movement;
   vec4 global_camera_position;
   float global_gamma;
};

uniform sampler2D hdrBuffer;
uniform float exposure;
uniform bool enable_exposure;

uniform bool BlurHorizontal;
uniform bool enableBloom;

float BlurWeight[5] = {0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162};

vec3 blur()
{
    vec2 tex_offset = 1.0 / textureSize(hdrBuffer, 0); // gets size of single texel
    vec3 result = texture(hdrBuffer, texCoords).rgb * BlurWeight[0];
    if(BlurHorizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
           result += texture(hdrBuffer, texCoords + vec2(tex_offset.x * i, 0.0)).rgb * BlurWeight[i];
           result += texture(hdrBuffer, texCoords - vec2(tex_offset.x * i, 0.0)).rgb * BlurWeight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(hdrBuffer, texCoords + vec2(0.0, tex_offset.y * i)).rgb * BlurWeight[i];
            result += texture(hdrBuffer, texCoords - vec2(0.0, tex_offset.y * i)).rgb * BlurWeight[i];
        }
    }
     
    return result;
}

vec3 hdrAndGamma()
{
    vec3 hdrColor = texture(hdrBuffer, texCoords).rgb;

    // apply bloom
    vec3 bloomColor = blur();
    if(enableBloom)
        hdrColor += bloomColor; // additive blending

    vec3 result;
    if(enable_exposure)
    {
        // exposure
        result = vec3(1.0) - exp(-hdrColor * exposure);
    }
    else
    {
        // reinhard
        result = hdrColor / (hdrColor + vec3(1.0));
    }

    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / global_gamma));

    return result;
}

void main()
{
    FragColor = vec4(hdrAndGamma(),1.0);
}