#ifndef ENCODER_H
#define ENCODER_H
#define PIT0                            (CCU60_CH0 )                            // 使用的周期中断编号
#define ENCODER_DIR_L                     (TIM4_ENCODER)                         // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR__L_PULSE               (TIM4_ENCODER_CH1_P02_8)               // PULSE 对应的引脚
#define ENCODER_DIR__L_DIR                 (TIM4_ENCODER_CH2_P00_9)               // DIR 对应的引脚

#define ENCODER_DIR_R                     (TIM2_ENCODER)                         // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR__R_PULSE               (TIM2_ENCODER_CH1_P33_7)               // PULSE 对应的引脚
#define ENCODER_DIR__R_DIR                 (TIM2_ENCODER_CH2_P33_6)               // DIR 对应的引脚
int Get_Left_Motor_Speed(void);

int Get_Right_Motor_Speed(void);

void Encoder_init(void);
#endif