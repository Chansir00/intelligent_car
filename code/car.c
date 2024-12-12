#include "zf_common_headfile.h"

uint8_t flag1=0;
uint8_t flag2=0;
uint8_t flag3=0;
extern uint8_t Car_State;
extern uint8_t Run;
extern int16 L_corner_flag;
extern int16 R_corner_flag;
extern uint8 left_lose,right_lose;
extern int8_t offset;
extern car_direction car_dir = STOP;
extern int flag;
extern bool in_roundabout;
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
    adc_ini();



}


void Car_tradege(void)
{
<<<<<<< Updated upstream

//    switch (car_dir)
//    {
//    case 0:
//        Car_stop();
//        break;
//    case 1:
//        Car_streight();
//        break;
//    case 2:
//        Car_left();
//        break;
//    case 3:
//        Car_right();
//        break;
//    case 4:
//        Car_left_circle();
//        break;
//    case 5:
//        Car_right_circle();
//        break;
//    default:
//        break;
//    }
=======
    if(Run==1)
    {
        if(R_corner_flag>=1&&left_lose<=40)  //判断为右环
        {
            Car_State=1;
        }
        else if(left_lose>=70 && right_lose>=70)
            Car_State=4;
        else if(R_corner_flag&&L_corner_flag)
            Car_State=4;
        else if(left_lose<30&&right_lose<30)
            Car_State=4;
        else
            Car_State=1;
    }
    else
        Car_State=0;

>>>>>>> Stashed changes
}

void right_circle()
{
        Set_Left_Motor_Duty(9000);
        Set_Right_Motor_Duty(5000);
}

void Car_stop(void)
{

    Set_Left_Motor_Duty(0);
    Set_Right_Motor_Duty(0);
}




