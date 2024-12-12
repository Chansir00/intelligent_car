#include "zf_common_headfile.h"




int Get_Left_Motor_Speed(void)
{
    int left_speed;
    left_speed = -(int)encoder_get_count(ENCODER_QUADDEC1);
    encoder_clear_count(ENCODER_QUADDEC1);
    return left_speed;
}


int Get_Right_Motor_Speed(void)
{
    int right_speed;
    right_speed = (int)encoder_get_count(ENCODER_QUADDEC2);
    encoder_clear_count(ENCODER_QUADDEC2);
    return right_speed;
}

void Encoder_init(void)
{
    encoder_quad_init(ENCODER_QUADDEC1, ENCODER_QUADDEC_A1, ENCODER_QUADDEC_B1);
    encoder_quad_init(ENCODER_QUADDEC2, ENCODER_QUADDEC_A2, ENCODER_QUADDEC_B2);
    pit_ms_init(PIT0, 10);                                                     // 鍒濆鍖� PIT0 涓哄懆鏈熶腑鏂� 100ms 鍛�
    pit_ms_init(PIT1, 50);
}
