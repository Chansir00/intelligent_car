#include "zf_common_headfile.h"


// 宸︾數鏈洪�熷害闂幆鐩稿叧鍙橀噺
int left_motor_error,left_motor_next_error,left_motor_last_error;
float left_motor_increment,left_motor_actual;
float left_motor_p,left_motor_i,left_motor_d;
// 鍙崇數鏈洪�熷害闂幆鐩稿叧鍙橀噺
int right_motor_error,right_motor_next_error,right_motor_last_error;
float right_motor_increment,right_motor_actual;
float right_motor_p,right_motor_i,right_motor_d;

void Init_Motor(void)
{   
    
    //宸︾數鏈烘帶鍒跺紩鑴�
    pwm_init(LEFT_MOTOR_PWM, MOTOR_FREQ, 0);
    pwm_init(LEFT_MOTOR_DIR, MOTOR_FREQ, 0);
    // 鍙崇數鏈烘帶鍒跺紩鑴�
    pwm_init(RIGHT_MOTOR_PWM, MOTOR_FREQ, 0);
    pwm_init(RIGHT_MOTOR_DIR, MOTOR_FREQ, 0);
    //宸︾數鏈洪�熷害闂幆鍙傛暟
    left_motor_p = 120;
    left_motor_i = 15;
    left_motor_d = 76;
    // 鍙崇數鏈洪�熷害闂幆鍙傛暟
    right_motor_p = 120;
    right_motor_i = 15;
    right_motor_d = 76;
}

void Set_Left_Motor_Duty(int duty)
{
    if (duty > 0)
    {
        pwm_set_duty(LEFT_MOTOR_DIR, duty); // Set direction forward
    }
    else
    {
        duty = -duty; // Make duty positive
        pwm_set_duty(LEFT_MOTOR_DIR, duty); // Set direction backward
    }
    pwm_set_duty(LEFT_MOTOR_PWM, duty); // Set PWM duty cycle
}
void Set_Right_Motor_Duty(int duty)
{
    if (duty > 0)
    {
        pwm_set_duty(RIGHT_MOTOR_DIR, 1); // Set direction forward
    }
    else
    {
        duty = -duty; // Make duty positive
        pwm_set_duty(RIGHT_MOTOR_DIR, 0); // Set direction backward

    }
    pwm_set_duty(RIGHT_MOTOR_PWM, duty); // Set PWM duty cycle
}


int Pid_Left_Motor(int hope_speed, int rear_speed)
{
    // 閫熷害璇樊
    left_motor_error = hope_speed - rear_speed;
    // 澧為噺璁＄畻
    left_motor_increment = left_motor_p * (left_motor_error) + left_motor_i * (left_motor_error - left_motor_next_error) + left_motor_d * (left_motor_error - 2 * left_motor_next_error + left_motor_last_error);
    left_motor_actual += left_motor_increment;
    // 缁撴灉闄愬箙
    if(left_motor_actual > 10000)
        left_motor_actual = 10000;
    else if(left_motor_actual < -10000)
        left_motor_actual = -10000;
    // 璇樊杩唬
    left_motor_last_error = left_motor_next_error;
    left_motor_next_error = left_motor_error;
    return (int)left_motor_actual;
}
int Pid_Right_Motor(int hope_speed, int rear_speed)
{
    // 閫熷害璇樊
    right_motor_error = hope_speed - rear_speed;
    // 澧為噺璁＄畻
    right_motor_increment = right_motor_p * (right_motor_error) + right_motor_i * (right_motor_error - right_motor_next_error) + right_motor_d * (right_motor_error - 2 * right_motor_next_error + right_motor_last_error);
    right_motor_actual += right_motor_increment;
    // 缁撴灉闄愬箙
    if(right_motor_actual > 10000)
        right_motor_actual = 10000;
    else if(right_motor_actual < -10000)
        right_motor_actual = -10000;
    // 璇樊杩唬
    right_motor_last_error = right_motor_next_error;
    right_motor_next_error = right_motor_error;
    return (int)right_motor_actual;
}

void Turn(int angle, int speed)
{
    // 璁＄畻宸﹀彸鐢垫満鐨勭洰鏍囬�熷害
    int left_motor_speed = speed - angle * 10; // 10鏄竴涓父鏁帮紝鍙互鏍规嵁瀹為檯鎯呭喌璋冩暣
    int right_motor_speed = speed + angle * 10;

    // 璁剧疆宸﹀彸鐢垫満鐨勯�熷害
    Set_Left_Motor_Duty(Pid_Left_Motor(left_motor_speed, Get_Left_Motor_Speed()));
    Set_Right_Motor_Duty(Pid_Right_Motor(right_motor_speed, Get_Right_Motor_Speed()));
}
