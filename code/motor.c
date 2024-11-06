#include "zf_common_headfile.h"

    // 外层PID参数
float outer_pid_p = 2.0;
float outer_pid_i = 0.5;
float outer_pid_d = 0.1;

// 内层PID参数
float inner_pid_p = 1.0;
float inner_pid_i = 0.2;
float inner_pid_d = 0.05;

float outer_error, outer_last_error = 0;
float inner_error, inner_last_error = 0;
float outer_integral = 0;
void Init_Motor(void)
{   
    
    //宸︾數鏈烘帶鍒跺紩鑴�
    pwm_init(LEFT_MOTOR_PWM, MOTOR_FREQ, 0);
    pwm_init(LEFT_MOTOR_DIR, MOTOR_FREQ, 0);
    // 鍙崇數鏈烘帶鍒跺紩鑴�
    pwm_init(RIGHT_MOTOR_PWM, MOTOR_FREQ, 0);
    pwm_init(RIGHT_MOTOR_DIR, MOTOR_FREQ, 0);
    //宸︾數鏈洪�熷害闂幆鍙傛暟

}

//void Set_Left_Motor_Duty(int duty)
//{
//    if (duty > 0)
//    {
//        pwm_set_duty(LEFT_MOTOR_DIR, 1); // Set direction forward
//    }
//    else
//    {
//        duty = -duty; // Make duty positive
//        pwm_set_duty(LEFT_MOTOR_DIR, 0); // Set direction backward
//    }
//    pwm_set_duty(LEFT_MOTOR_PWM, duty); // Set PWM duty cycle
//}
void Set_Left_Motor_Duty(int duty)
{
    if(duty >=0)
    {
        if(duty > MOTOR_A_DUTY)
            duty = MOTOR_A_DUTY;

        pwm_set_duty(LEFT_MOTOR_PWM, duty);
        pwm_set_duty(LEFT_MOTOR_DIR, 0);
    }
    else
    {
        if(duty < -MOTOR_B_DUTY)
            duty = -MOTOR_B_DUTY;

        pwm_set_duty(LEFT_MOTOR_PWM, -duty);
        pwm_set_duty(LEFT_MOTOR_DIR, 10000);
    }
}
//void Set_Right_Motor_Duty(int duty)
//{
//    if (duty > 0)
//    {
//        pwm_set_duty(RIGHT_MOTOR_DIR, 1); // Set direction forward
//    }
//    else
//    {
//        duty = -duty; // Make duty positive
//        pwm_set_duty(RIGHT_MOTOR_DIR, 0); // Set direction backward
//
//    }
//    pwm_set_duty(RIGHT_MOTOR_PWM, duty); // Set PWM duty cycle
//}
void Set_Right_Motor_Duty(int duty)
{
    if(duty >=0)
    {
        if(duty > MOTOR_A_DUTY)
            duty = MOTOR_A_DUTY;

        pwm_set_duty(RIGHT_MOTOR_PWM, duty);
        pwm_set_duty(RIGHT_MOTOR_DIR, 0);
    }
    else
    {
        if(duty < -MOTOR_B_DUTY)
            duty = -MOTOR_B_DUTY;

        pwm_set_duty(RIGHT_MOTOR_PWM, -duty);
        pwm_set_duty(RIGHT_MOTOR_DIR, 10000);
    }
}
int calculate_outer_pid(float desired_position, float current_position) {
    outer_error = desired_position - current_position;
    outer_integral += outer_error; // 积分
    float outer_derivative = outer_error - outer_last_error; // 微分

    float output = outer_pid_p * outer_error +
                   outer_pid_i * outer_integral +
                   outer_pid_d * outer_derivative;

    outer_last_error = outer_error; // 更新上一轮误差
    return (int)output; // 输出作为希望速度
}

int calculate_inner_pid(int desired_speed, int left_speed, int right_speed) {
    int average_speed = (left_speed + right_speed) / 2;
    int speed_error = desired_speed - average_speed;

    float inner_increment = inner_pid_p * speed_error +
                            inner_pid_i * (speed_error - inner_last_error) +
                            inner_pid_d * (speed_error - 2 * inner_last_error);

    inner_last_error = speed_error; // 更新上一轮误差

    return (int)(inner_increment); // 返回增量
}
void adjust_motor_speed() {
    float desired_angle = 0; // 目标角度（保持车辆在赛道中间）

    // 计算当前赛道的角度并限幅
    float current_angle = Get_angle(L_corner_row, L_corner_col, R_corner_row, R_corner_col, IMAGE_H, IMAGE_W);
    float limited_angle = limit(current_angle, 30);

    // 计算偏移量：赛道中线相对于摄像头中线的偏移
    uint8_t offset = calculate_offset(); // 调用偏移量计算函数

    // 使用偏移量和角度计算期望速度增量
    uint16_t speed_adjustment = calculate_outer_pid(0, offset);

    // 获取当前左右轮速度
    uint16_t left_speed = Get_Left_Motor_Speed();
    uint16_t right_speed = Get_Right_Motor_Speed();

    // 计算基础速度并加上调整值
    uint16_t base_speed = 4000; // 可以根据需要调整基础速度
    uint16_t desired_speed_left = base_speed - speed_adjustment;
    uint16_t desired_speed_right = base_speed + speed_adjustment;

    uint16_t motor_increment_left = calculate_inner_pid(desired_speed_left, left_speed, left_speed);
    uint16_t motor_increment_right = calculate_inner_pid(desired_speed_right, right_speed, right_speed);
    Set_Left_Motor_Duty(4000);
    Set_Right_Motor_Duty(4000);
    // 调整电机速度并设置限幅
    Set_Left_Motor_Duty((int)(desired_speed_left + motor_increment_left));
    Set_Right_Motor_Duty((int)(desired_speed_right + motor_increment_right));


    // 发送调试信息
    uart_write_byte(UART_INDEX, offset);
}




