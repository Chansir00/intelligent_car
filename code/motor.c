#include "zf_common_headfile.h"


// PID参数
float kp_steer = 0.09, ki_steer = 0.0, kd_steer = 0.0; // 转向PID参数
float kp_speedf  = 1200.0, ki_speedf =45.0, kd_speedf = 0.00; // 速度控制PID参数
float kp_speedr  = 1200.0, ki_speedr =45.0, kd_speedr = 00.00; // 速度控制PID参数
float Add_CCR_f = 0,pwm_CCR_f=0;
float Add_CCR_r = 0,pwm_CCR_r=0;
// 偏差变量

// PID控制变量
float error_steer = 0, error_prev_steer = 0, integral_steer = 0;
float error_speed_f = 0, error_prev_speed_f = 0, error_pprev_speed_f = 0;
float error_speed_r = 0, error_prev_speed_r = 0, error_pprev_speed_r = 0;
int desired_speed_left = 0;
int desired_speed_right = 0;

// 使用内层PID控制对左右电机速度进行细微调整
int motor_increment_left = 0;
int motor_increment_right =0;

int base_speed = 7; // 可根据需要调整基础速度
int speed_adjustment =0; // 调用PID控制函数，基于偏差计算转向调整量
extern int left_speed ;
extern int right_speed ;

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
        pwm_set_duty(RIGHT_MOTOR_DIR ,0);
    }
    else
    {
        if(duty < -MOTOR_B_DUTY)
            duty = -MOTOR_B_DUTY;

        pwm_set_duty(RIGHT_MOTOR_PWM, -duty);
        pwm_set_duty(RIGHT_MOTOR_PWM, 10000);
    }
}
// 转向PID控制器：根据偏差调整差速
float pid_steer(int offset)
{
    static float integral_steer = 0;
    static float error_prev_steer = 0;
    static float derivative_filtered_steer = 0;
    int error_steer = offset;

    // 积分项限制，防止积分过大
    const float integral_limit = 100; // 根据需要调整限制值
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
float pid_f_speed(int target_speed, int current_speed)
{
    error_speed_f=(float)target_speed - current_speed;
    if(abs(error_speed_f)>10)
    {
        Add_CCR_f = kp_speedf*(error_speed_f-error_prev_speed_f )+0.3*ki_speedf*(error_speed_f)+kd_speedf*(error_speed_f+error_pprev_speed_f-2*error_prev_speed_f);
        //PWM占空比增加的部分=比例环节+积分环节+微分环节
    }
    else
    {
        Add_CCR_f = kp_speedf*(error_speed_f-error_prev_speed_f )+ki_speedf*(error_speed_f)+kd_speedf*(error_speed_f+error_pprev_speed_f-2*error_prev_speed_f);
        //PWM占空比增加的部分=比例环节+积分环节+微分环节
    }
    //设定速度-实时速度
    if(Add_CCR_f<-1||Add_CCR_f>1)                                                //限幅，微小变化不更改，减少抖动
    {
     pwm_CCR_f+=Add_CCR_f;
    }


      if(pwm_CCR_f>9999)
        pwm_CCR_f=9999;
    if(pwm_CCR_f<0)
        pwm_CCR_f=0;
    error_pprev_speed_f=error_prev_speed_f ;                                                             //把上一次误差赋值给上上次误差
    error_prev_speed_f =error_speed_f;                                                                                                     //把最新误差赋值给上次误差
    return pwm_CCR_f;                                                                                                      //返回PWM新的占空比值
}


float pid_r_speed(int target_speed, int current_speed)
{
    error_speed_r=(float)target_speed - current_speed;
    if(abs(error_speed_r)>10)
    {
        Add_CCR_r = kp_speedr*(error_speed_r-error_prev_speed_r )+0.3*ki_speedr*(error_speed_r)+kd_speedr*(error_speed_r+error_pprev_speed_r-2*error_prev_speed_r);
        //PWM占空比增加的部分=比例环节+积分环节+微分环节
    }
    else
    {
        Add_CCR_r = kp_speedr*(error_speed_r-error_prev_speed_r )+ki_speedr*(error_speed_r)+kd_speedr*(error_speed_r+error_pprev_speed_r-2*error_prev_speed_r);
        //PWM占空比增加的部分=比例环节+积分环节+微分环节
    }
    //设定速度-实时速度
    if(Add_CCR_r<-1||Add_CCR_r>1)                                                //限幅，微小变化不更改，减少抖动
    {
     pwm_CCR_r+=Add_CCR_r;
    }


      if(pwm_CCR_r>9999)
        pwm_CCR_r=9999;
    if(pwm_CCR_r<0)
        pwm_CCR_r=0;
    error_pprev_speed_r=error_prev_speed_r ;                                                             //把上一次误差赋值给上上次误差
    error_prev_speed_r =error_speed_r;                                                                                                     //把最新误差赋值给上次误差
    return pwm_CCR_r;                                                                                                      //返回PWM新的占空比值
}
void adjust_motor_speed(int offset) {
    // 获取当前左右轮速度

    // 基础速度和转向调整

    speed_adjustment = pid_steer(abs(offset)); // 调用PID控制函数，基于偏差计算转向调整量


    // 根据offset方向进行转向判断
    if (offset > 0) {
        // 向左偏，需向右转，增加左轮速度，减少右轮速度
        //uart_write_string(UART_INDEX, "Left Turn\n");
        desired_speed_left = base_speed +speed_adjustment;
        desired_speed_right = base_speed -speed_adjustment;

        // 使用内层PID控制对左右电机速度进行细微调整
        motor_increment_left = pid_f_speed(desired_speed_left,  left_speed);
        motor_increment_right = pid_r_speed(desired_speed_right, right_speed);

        // 应用最终速度调整
        Set_Left_Motor_Duty((int)(motor_increment_left));
        Set_Right_Motor_Duty((int)(motor_increment_right));

    } else if (offset <0) {
        // 向右偏，需向左转，增加右轮速度，减少左轮速度
        //uart_write_string(UART_INDEX, "Right Turn\n");
        desired_speed_left = base_speed-speed_adjustment;
        desired_speed_right = base_speed+speed_adjustment ;

        // 使用内层PID控制对左右电机速度进行细微调整
        motor_increment_left = pid_f_speed(desired_speed_left,  left_speed);
        motor_increment_right = pid_r_speed(desired_speed_right, right_speed);

        // 应用最终速度调整
        Set_Left_Motor_Duty((int)( motor_increment_left));
        Set_Right_Motor_Duty((int)(motor_increment_right));
    }else
    {
        motor_increment_left = pid_f_speed(base_speed, left_speed);
        motor_increment_right = pid_r_speed(base_speed,right_speed);
        Set_Left_Motor_Duty((int)( motor_increment_left));
        Set_Right_Motor_Duty((int)(motor_increment_right));
    }
    //printf("%d,%d,%d\r\n",desired_speed_left,desired_speed_right,15);


}



