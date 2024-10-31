#ifndef __MOTOR_H_
#define __MOTOR_H_



// 电机PWM引脚
#define LEFT_MOTOR_PWM      ATOM1_CH4_P02_4
#define LEFT_MOTOR_DIR      ATOM1_CH5_P02_5
#define RIGHT_MOTOR_PWM     ATOM1_CH6_P02_6
#define RIGHT_MOTOR_DIR     ATOM1_CH7_P02_7
// 电机频率
#define MOTOR_FREQ          13333
// 电机限幅
#define MOTOR_A_DUTY        4000
// 电机限幅
#define MOTOR_B_DUTY        4000

void Init_Motor(void);

void Set_Left_Motor_Duty(int duty);

void Set_Right_Motor_Duty(int duty);

int Pid_Left_Motor(int hope_speed, int rear_speed);

int Pid_Right_Motor(int hope_speed, int rear_speed);


#endif
