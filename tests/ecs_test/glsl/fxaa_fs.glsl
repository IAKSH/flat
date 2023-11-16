#version 320 es

precision highp float;
precision highp int;

in vec2 in_uv;
out vec4 out_color;
uniform sampler2D in_color;
uniform vec2 resolution;

#define UP_LEFT      0
#define UP           1
#define UP_RIGHT     2
#define LEFT         3
#define CENTER       4
#define RIGHT        5
#define DOWN_LEFT    6
#define DOWN         7
#define DOWN_RIGHT   8

#define EDGE_THRESHOLD_MIN  0.0312
#define EDGE_THRESHOLD_MAX  0.125
#define SUBPIXEL_QUALITY    0.75
#define GRADIENT_SCALE      0.25

#define STEP_COUNT_MAX   12
float QUALITY(int i) {
    if (i < 5) return 1.0;
    if (i == 5) return 1.5;
    if (i < 10) return 2.0;
    if (i == 10) return 4.0;
    if (i == 11) return 8.0;
    return 8.0;
}

vec2 STEP_MAT[] = vec2[9](
    vec2(-1.0, 1.0), vec2( 0.0, 1.0), vec2( 1.0, 1.0),
    vec2(-1.0, 0.0), vec2( 0.0, 0.0), vec2( 1.0, 0.0),
    vec2(-1.0,-1.0), vec2( 0.0,-1.0), vec2( 1.0,-1.0)
);

float RGB2LUMA(vec3 rgb_color) {
    return dot(vec3(0.299, 0.578, 0.114), rgb_color);
}

vec4 fxaa() {
	// ������Ļ�ռ���ƬԪ�������߳�
	vec2 uv_step = vec2(1.0 / resolution.x, 1.0 / resolution.y);
	
	// ���㵱ǰƬԪ���ܵ�����ֵ
	float luma_mat[9];
	for(int i = 0;i < 9;i++) {
		luma_mat[i] = RGB2LUMA(texture(in_color,in_uv + uv_step * STEP_MAT[i]).rgb);
	}

	float luma_max = max(luma_mat[CENTER], max(max(luma_mat[LEFT], luma_mat[RIGHT]), max(luma_mat[UP], luma_mat[DOWN])));
	float luma_min = min(luma_mat[CENTER], min(min(luma_mat[LEFT], luma_mat[RIGHT]), min(luma_mat[UP], luma_mat[DOWN])));
	// ���3x3ɫ���ڵ����Ȳ��첢�����Ǿ�����
	if(luma_max - luma_min < max(EDGE_THRESHOLD_MIN, luma_max * EDGE_THRESHOLD_MAX)) {
		return texture(in_color, in_uv);
	}

	// ������ֱ������ݶ�
    float luma_horizontal = 
        abs(luma_mat[UP_LEFT]  + luma_mat[DOWN_LEFT]  - 2.0*luma_mat[LEFT]) +
        abs(luma_mat[UP_RIGHT] + luma_mat[DOWN_RIGHT] - 2.0*luma_mat[RIGHT]) +
        abs(luma_mat[UP] + luma_mat[DOWN] - 2.0*luma_mat[CENTER]);
    // ����ˮƽ������ݶ�
    float luma_vertial =
        abs(luma_mat[UP_LEFT]   + luma_mat[UP_RIGHT]   - 2.0*luma_mat[UP]) +
        abs(luma_mat[DOWN_LEFT] + luma_mat[DOWN_RIGHT] - 2.0*luma_mat[DOWN]) +
        abs(luma_mat[LEFT] + luma_mat[RIGHT] - 2.0*luma_mat[CENTER]);
    // ��ֱ������ݶȴ�Ļ����Ǿ�˵����Ե������ˮƽ�����
    bool is_horizontal = abs(luma_horizontal) > abs(luma_vertial);
    
    // �������ű�Ե�ķ��߷������£����ң����ݶ�
    float grandient_down_left = (is_horizontal ? luma_mat[DOWN] : luma_mat[LEFT]) - luma_mat[CENTER];
    float grandient_up_right = (is_horizontal ? luma_mat[UP] : luma_mat[RIGHT]) - luma_mat[CENTER];
    // ���������ݶȴ���������ݶȣ����������ų��µģ���ֱ����ͬ��
    bool is_down_left = abs(grandient_down_left) > abs(grandient_up_right);
    float gradient_start = is_down_left ? grandient_down_left : grandient_up_right;
    
    vec2 step_tangent = (is_horizontal ? vec2(1.0, 0.0) : vec2(0.0, 1.0)) * uv_step;
    vec2 step_normal = (is_down_left ? -1.0 : 1.0) * (is_horizontal ? vec2(0.0, 1.0) : vec2(1.0, 0.0)) * uv_step;
    
    // ���ŷ��߷���ǰ��0.5�񣬵���ƬԪ�ı߽�
    vec2 uv_start = in_uv + 0.5 * step_normal;
    // �߽總������ƬԪ���ȵľ�ֵ
    float luma_average_start = luma_mat[CENTER] + 0.5 * gradient_start;
    
    // ��������
    vec2 uv_forward  = uv_start;
    vec2 uv_backward = uv_start;
    
    float delta_luma_forward = 0.0;
    float delta_luma_backward = 0.0;
    
    bool reached_forward   = false;
    bool reached_backward = false;
    bool reached_both      = false;
    
    for(int i = 1; i < STEP_COUNT_MAX; i++){
        if(!reached_forward)  uv_forward += QUALITY(i) * step_tangent;
        if(!reached_backward) uv_backward += - QUALITY(i) * step_tangent;
        
        // ������ƶ��������ֵ
        delta_luma_forward = RGB2LUMA(texture(in_color, uv_forward).rgb) - luma_average_start;
        delta_luma_backward = RGB2LUMA(texture(in_color, uv_backward).rgb) - luma_average_start;
        
        // ǰ��벿������ƽ�����ȼ�����ݶȣ��������������ݶȻ�ƫС
        // ����ֻ��Ϊ���ҵ��˵㣬���Զ� gradient_start ������������ 1/4
        reached_forward = abs(delta_luma_forward) > GRADIENT_SCALE * abs(gradient_start);
        reached_backward = abs(delta_luma_backward) > GRADIENT_SCALE * abs(gradient_start);
        reached_both = reached_forward && reached_backward;
        
        if(reached_both) break;
    }
    // �����ϱ���
    float length_forward = max(abs(uv_forward - uv_start).x, abs(uv_forward - uv_start).y);
    float length_backward = max(abs(uv_backward - uv_start).x, abs(uv_backward - uv_start).y);
    bool is_forward_near = length_forward < length_backward;
    float pixel_offset = -1.0 * ((is_forward_near ? length_forward : length_backward) / (length_forward + length_backward)) + 0.5;

    // �жϸ��ӽӽ����Ǹ��㣬���Լ�����ɫ�Ƿ�ӽ�������ӽ��ǾͲ��û��
    if( ((is_forward_near ? delta_luma_forward : delta_luma_backward) < 0.0) ==
        (luma_mat[CENTER] < luma_average_start)) pixel_offset = 0.0;
    
    float luma_average_center = 0.0;
    float average_weight_mat[] = float[9](
        1.0, 2.0, 1.0,
        2.0, 0.0, 2.0,
        1.0, 2.0, 1.0
    );
    for (int i = 0; i < 9; i++) luma_average_center += average_weight_mat[i] * luma_mat[i];
    luma_average_center /= 12.0;
    // ���鹫ʽ
    float subpixel_luma_range = clamp(abs(luma_average_center - luma_mat[CENTER]) / (luma_max - luma_min), 0.0, 1.0);
    float subpixel_offset = (-2.0 * subpixel_luma_range + 3.0) * subpixel_luma_range * subpixel_luma_range;
    subpixel_offset = subpixel_offset * subpixel_offset * SUBPIXEL_QUALITY;
    
    pixel_offset = max(pixel_offset, subpixel_offset);
    
    return texture(in_color, in_uv + pixel_offset * step_normal);
}

void main()
{
    out_color = fxaa();
}
