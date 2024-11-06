#include "zf_common_headfile.h"

uint8_t flag1=0;
uint8_t flag2=0;
uint8_t flag3=0;


extern car_direction car_dir = STOP;
void Car_Init(void)
{
    if(flag1 ==0)
        uart_write_byte (UART_INDEX, 0x01);
        flag1 = 1;
    Encoder_init();
    Init_Motor();
    tft180_set_dir(TFT180_CROSSWISE);
    tft180_init();
    mt9v03x_init();
    Uart_init();
    key_init(10);


}
void kernel(void)
{
    //tftsplayimage032_zoom(bin_image[0], image_w, image_h, image_w, image_h,0,0);
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
    if(flag3 ==0)
        uart_write_byte (UART_INDEX, 0x03);
        flag3 = 1;
    adjust_motor_speed();
//    Set_Left_Motor_Duty(9000);
//    Set_Right_Motor_Duty(9000);
}

void Car_left(void)
{
    Set_Left_Motor_Duty(6000);
    Set_Right_Motor_Duty(9000);
}

void Car_right(void)
{
    Set_Left_Motor_Duty(9000);
    Set_Right_Motor_Duty(6000);
}


void Car_left_circle(void)
{
    Set_Left_Motor_Duty(6000);
    Set_Right_Motor_Duty(9000);
}


void Car_right_circle(void)
{
    Set_Left_Motor_Duty(9000);
    Set_Right_Motor_Duty(6000);
}


void Car_stop(void)
{
    if(flag1 ==0)
        uart_write_byte (UART_INDEX, 0x01);
        flag1 = 1;
    Set_Left_Motor_Duty(0);
    Set_Right_Motor_Duty(0);
}

