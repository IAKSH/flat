#version 320 es
precision highp float;

out vec4 color;
in vec2 texCoords;

uniform sampler2D hdrBuffer;
uniform float exposure;
uniform bool enable_exposure;

layout (std140) uniform GFXGlobalUBO
{
   mat4 global_projection;
   mat4 global_view;
   mat4 view_without_movement;
   vec4 global_camera_position;
   float global_gamma;
};

void main()
{
    vec3 hdrColor = texture(hdrBuffer, texCoords).rgb;

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

    color = vec4(result, 1.0f);
}