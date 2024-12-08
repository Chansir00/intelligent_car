#include "zf_common_headfile.h"

// PID参数
float kp_steer = 10.0, ki_steer = 0.0, kd_steer = 0.1; // 转向PID参数
float kp_speed = 3.0, ki_speed = 0.0, kd_speed = 0.1; // 速度控制PID参数

// 偏差变量

// PID控制变量
float error_steer = 0, error_prev_steer = 0, integral_steer = 0;
float error_speed = 0, error_prev_speed = 0, integral_speed = 0;


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

        pwm_set_duty(LEFT_MOTOR_PWM, 0);
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

        pwm_set_duty(RIGHT_MOTOR_PWM, 0);
        pwm_set_duty(RIGHT_MOTOR_DIR, 10000);
    }
}
// 转向PID控制器：根据偏差调整差速
float pid_steer(int8_t offset)
{
    static float integral_steer = 0;
    static float error_prev_steer = 0;
    static float derivative_filtered_steer = 0;
    float error_steer = offset;

    // 积分项限制，防止积分过大
    const float integral_limit = 5000; // 根据需要调整限制值
    integral_steer += error_steer;
    if (integral_steer > integral_limit)
        integral_steer = integral_limit;
    else if (integral_steer < -integral_limit)
        integral_steer = -integral_limit;

    // 微分项滤波
    float derivative_steer = error_steer - error_prev_steer;
    derivative_filtered_steer = 0.9 * derivative_filtered_steer + 0.1 * derivative_steer;

    // 更新上次误差
    error_prev_steer = error_steer;

    // PID 计算
    return kp_steer * error_steer + ki_steer * integral_steer + kd_steer * derivative_filtered_steer;
}

// 速度PID控制函数
float pid_speed(uint16_t target_speed, uint16_t current_speed)
{
    static float integral_speed = 0;
    static float error_prev_speed = 0;
    float error_speed = target_speed - current_speed;
    integral_speed += error_speed;
    float derivative_speed = error_speed - error_prev_speed;
    error_prev_speed = error_speed;
    return kp_speed * error_speed + ki_speed * integral_speed + kd_speed * derivative_speed;
}
void adjust_motor_speed(int8_t offset) {
    // 获取当前左右轮速度

    uint16_t left_speed = Get_Left_Motor_Speed();
    uint16_t right_speed = Get_Right_Motor_Speed();


    // 基础速度和转向调整
    uint16_t base_speed = 3000; // 可根据需要调整基础速度
    int16_t speed_adjustment = pid_steer(offset); // 调用PID控制函数，基于偏差计算转向调整量
    uart_write_byte(UART_INDEX,left_speed);
    uart_write_byte(UART_INDEX,base_speed);

    // 根据offset方向进行转向判断
    if (offset > 0) {
        // 向左偏，需向右转，增加左轮速度，减少右轮速度
        //uart_write_string(UART_INDEX, "Left Turn\n");
        uint16_t desired_speed_left = base_speed + speed_adjustment;
        uint16_t desired_speed_right = base_speed - speed_adjustment;

        // 使用内层PID控制对左右电机速度进行细微调整
        uint16_t motor_increment_left = pid_speed(desired_speed_left,  left_speed);
        uint16_t motor_increment_right = pid_speed(desired_speed_right, right_speed);

        // 应用最终速度调整
        Set_Left_Motor_Duty((int)(base_speed));
        Set_Right_Motor_Duty((int)(base_speed));

    } else if (offset < 0) {
        // 向右偏，需向左转，增加右轮速度，减少左轮速度
        //uart_write_string(UART_INDEX, "Right Turn\n");
        uint16_t desired_speed_left = base_speed - speed_adjustment;
        uint16_t desired_speed_right = base_speed + speed_adjustment;

        // 使用内层PID控制对左右电机速度进行细微调整
        uint16_t motor_increment_left = pid_speed(desired_speed_left,  left_speed);
        uint16_t motor_increment_right = pid_speed(desired_speed_right, right_speed);

        // 应用最终速度调整
        Set_Left_Motor_Duty((int)( base_speed));
        Set_Right_Motor_Duty((int)(base_speed));
    }

}




