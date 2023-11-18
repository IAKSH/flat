#version 320 es
precision highp float;

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D sceneTex;

// SobelËã×Ó±ßÔµ¼ì²â
const mat3 sx = mat3( 
    1.0, 2.0, 1.0, 
    0.0, 0.0, 0.0, 
   -1.0, -2.0, -1.0 
);

const mat3 sy = mat3( 
    1.0, 0.0, -1.0, 
    2.0, 0.0, -2.0, 
    1.0, 0.0, -1.0 
);

vec4 sobelEdgeDetection()
{
	vec2 x_1 = vec2(1.0/800.0, 0.0);    //the length of one texel
	vec2 y_1 = vec2(0.0, 1.0/600.0);    //same as above

    vec2 texSize = vec2(textureSize(sceneTex,0));

	mat3 I;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) 
            I[i][j] = length(texture(sceneTex, texCoords + vec2(float(i-1) / texSize.x,float(j-1) / texSize.y)).rgb); 
    }
	float gx = dot(sx[0], I[0]) + dot(sx[1], I[1]) + dot(sx[2], I[2]); 
	float gy = dot(sy[0], I[0]) + dot(sy[1], I[1]) + dot(sy[2], I[2]);


    float mag = length(vec2(gx, gy));
    return vec4(vec3(mag), 1.0);
}

const float limit = 0.99;

void main()
{
    FragColor = texture(sceneTex, texCoords);
    vec4 edgeDetectionColor = max(sobelEdgeDetection() - vec4(limit,limit,limit,0.0),vec4(0.0,0.0,0.0,0.0));
    if(dot(edgeDetectionColor.rgb,vec3(1.0,1.0,1.0)) > limit * 3.0)
        FragColor = vec4(0.0,0.0,0.0,1.0);
}