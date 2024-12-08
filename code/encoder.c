#include "zf_common_headfile.h"




int Get_Left_Motor_Speed(void)
{
    int left_speed;
    left_speed = -(int)encoder_get_count(ENCODER_DIR_L);
    encoder_clear_count(ENCODER_DIR_L);
    return left_speed;
}


int Get_Right_Motor_Speed(void)
{
    int right_speed;
    right_speed = (int)encoder_get_count(ENCODER_DIR_R);
    encoder_clear_count(ENCODER_DIR_R);
    return right_speed;
}

void Encoder_init(void)
{
    encoder_dir_init(ENCODER_DIR_L, ENCODER_DIR__L_PULSE, ENCODER_DIR__L_DIR);          // 鍒濆鍖栫紪鐮佸櫒妯″潡涓庡紩鑴� 甯︽柟鍚戝閲忕紪鐮佸櫒妯″紡
    encoder_dir_init(ENCODER_DIR_R, ENCODER_DIR__R_PULSE, ENCODER_DIR__R_DIR);          // 鍒濆鍖栫紪鐮佸櫒妯″潡涓庡紩鑴� 甯︽柟鍚戝閲忕紪鐮佸櫒妯″紡
    pit_ms_init(PIT0, 100);                                                     // 鍒濆鍖� PIT0 涓哄懆鏈熶腑鏂� 100ms 鍛�
}
