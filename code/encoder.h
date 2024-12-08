#ifndef ENCODER_H
#define ENCODER_H
#define PIT0                            (CCU60_CH0 )                            // 浣跨敤鐨勫懆鏈熶腑鏂紪鍙�
#define PIT1                            (CCU60_CH1 )                            // 使用的周期中断编号
#define ENCODER_QUADDEC1                 (TIM5_ENCODER)                         // 正交编码器对应使用的编码器接口
#define ENCODER_QUADDEC_A1               (TIM5_ENCODER_CH1_P10_3)               // A 相对应的引脚
#define ENCODER_QUADDEC_B1               (TIM5_ENCODER_CH2_P10_1)               // B 相对应的引脚

#define ENCODER_QUADDEC2                 (TIM2_ENCODER)                         // 正交编码器对应使用的编码器接口
#define ENCODER_QUADDEC_A2               (TIM2_ENCODER_CH1_P33_7)               // A 相对应的引脚
#define ENCODER_QUADDEC_B2               (TIM2_ENCODER_CH2_P33_6)               // B 相对应的引脚

int Get_Left_Motor_Speed(void);

int Get_Right_Motor_Speed(void);

void Encoder_init(void);
#endif
