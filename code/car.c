#include "zf_common_headfile.h"




extern car_direction car_dir = STOP;
void Car_Init(void)
{
    Encoder_init();
    Init_Motor();
    tft180_set_dir(TFT180_CROSSWISE);
    tft180_init();
    mt9v03x_init();
    Uart_init();
    key_init(10);
    uart_write_string(UART_INDEX, "init_ready");
}
void kernel(void)
{

    tft180_displayimage03x((const uint8_t *)Image_use_out[0], MT9V03X_W, MT9V03X_H);
    switch (car_dir)
    {
    case 0:
        Car_stop();
        break;
    case 1:
        Car_streight();
        break;
    case 2:
        Car_left();
        break;
    case 3:
        Car_right();
        break;
    case 4:
        Car_left_circle();
        break;
    case 5:
        Car_right_circle();
        break;
    default:
        break;
    }
}

void Car_streight(void)
{
    uart_write_string(UART_INDEX, "gp");
    Set_Left_Motor_Duty(90);
    Set_Right_Motor_Duty(90);
}

void Car_left(void)
{
    Set_Left_Motor_Duty(60);
    Set_Right_Motor_Duty(90);
}

void Car_right(void)
{
    Set_Left_Motor_Duty(90);
    Set_Right_Motor_Duty(60);
}


void Car_left_circle(void)
{
    Set_Left_Motor_Duty(60);
    Set_Right_Motor_Duty(90);
}


void Car_right_circle(void)
{
    Set_Left_Motor_Duty(90);
    Set_Right_Motor_Duty(60);
}


void Car_stop(void)
{
    uart_write_string(UART_INDEX, "stop");
    Set_Left_Motor_Duty(0);
    Set_Right_Motor_Duty(0);
}

