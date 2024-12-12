/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
const int TURN_TIME = 2000;
#pragma section all "cpu0_dsram"
<<<<<<< Updated upstream
extern uint8_t Car_State;
extern uint16_t desired_speed_left;
extern uint16_t desired_speed_right,motor_increment_left , motor_increment_right;
<<<<<<< HEAD
extern int8_t offset;
extern int16 L_corner_flag;
extern int16 R_corner_flag;
=======
>>>>>>> ccc3f4231577228addca1a3d483ab8c7f985445d
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
<<<<<<< HEAD

// **************************** 代码区域 ****************************



uint16 adc_data[CHANNEL_NUMBER];  // 存储每个通道的原始值
uint16 adc_result[CHANNEL_NUMBER];  // 存储每个通道的原始值
float normalized_values[CHANNEL_NUMBER];
int offsets[CHANNEL_NUMBER];        // 存储每个通道的偏移值
int total_offset = 0;              // 偏移值的总和
int offset_list[10];
int offset_adc = 0;
uint8_t time=0;
uint8_t time1=100;
=======
uint8_t Car_State =0;;
uint8_t Run=0;
extern uint16_t desired_speed_left;
extern uint16_t desired_speed_right,motor_increment_left , motor_increment_right;
extern int8_t offset;

// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设

// **************************** 代码区域 ****************************
int total_offset = 0;              // 偏移值的总和
int offset_list[10];
int offset_adc = 0;
int  time0;
int time1;
>>>>>>> Stashed changes
int temp =0;
int offset_test = -250;
extern int left_speed ;
extern int right_speed ;
<<<<<<< Updated upstream
int orin = 0;

=======

// **************************** 代码区域 ****************************


uint8 channel_index = 0;
adc_channel_enum channel_list[CHANNEL_NUMBER] =
{
     ADC_CHANNEL1,ADC_CHANNEL2,ADC_CHANNEL3,ADC_CHANNEL4
    //ADC_CHANNEL5, ADC_CHANNEL6, ADC_CHANNEL7, ADC_CHANNEL8
};
uint16 adc_data[CHANNEL_NUMBER];  // 存储每个通道的原始值
uint16 adc_result[CHANNEL_NUMBER];  // 存储每个通道的原始值
float normalized_values[CHANNEL_NUMBER];
int offsets[CHANNEL_NUMBER];        // 存储每个通道的偏移值
int total_offset = 0;              // 偏移值的总和
int offset_list[10];
int offset_adc = 0;
int time=0;
int temp =0;
int offset_test = -250;
extern int left_speed ;
extern int right_speed ;
int orin = 0;
int flag8 = 0;
int flag9=0;
>>>>>>> ccc3f4231577228addca1a3d483ab8c7f985445d
=======
extern int base_speed;
int orin = 0;
int flag =0;
>>>>>>> Stashed changes

int core0_main(void)
{
    clock_init();                   // ��ȡʱ��Ƶ��<��ر���>
    debug_init();                   // ��ʼ��Ĭ�ϵ��Դ���
    // �˴���д�û����� ���������ʼ�������
    Car_Init();
    // �˴���д�û����� ���������ʼ�������
    cpu_wait_event_ready();         // �ȴ����к��ĳ�ʼ�����                                        // ��Ҫ�Ⱥ��� ��Ȼ��ʾ����

    while (TRUE)
    {

<<<<<<< Updated upstream
        time++;
        // �˴���д��Ҫѭ��ִ�еĴ���
        //time++;
        if(time==20)
=======
        time0++;
        // �˴���д��Ҫѭ��ִ�еĴ���
        //time++;
        if(time0==20)
>>>>>>> Stashed changes
        {
            key_scanner();
            // 处理按键动作
            process_key_actions();
<<<<<<< Updated upstream
<<<<<<< HEAD
            printf("%d,%d,%d,%d,%d\r\n",  desired_speed_left,  desired_speed_right ,left_speed,right_speed,offset);
            if(Car_State==1)
            adjust_motor_speed(offset);

        }
        if(L_corner_flag == 1 || R_corner_flag==1)//左拐点存在标志)
        {
            printf("%d%d",L_corner_flag,L_corner_flag);
//            for(time1=100;time1>0;time1--)
//                adjust_motor_speed(30);

=======
            printf("%d,%d,%d,%d,%d\r\n",  desired_speed_left,  desired_speed_right ,left_speed,right_speed,total_offset);

        //    if(Car_State==1)
            adjust_motor_speed(total_offset);
            time=0;
        }
//        if(uart_read_byte (U                                                              ART_1))
//            Car_State=0;
        if (1)
        {
            total_offset = 0;  // 重置总偏移值
            for(channel_index = 0; channel_index < CHANNEL_NUMBER; channel_index ++)
            {
                adc_result[channel_index] = adc_mean_filter_convert(channel_list[channel_index], 10);
                normalized_values[channel_index] = normalize(adc_result[channel_index], ADC_MAX);
            }
            float diff_ratio = calculate_differential_ratio(normalized_values[0], normalized_values[1],normalized_values[2],normalized_values[3]);
            total_offset = diff_ratio *100;
            if(flag8==0)
            {
                orin = total_offset;
                flag8=1;
            }

            total_offset-=orin;
>>>>>>> ccc3f4231577228addca1a3d483ab8c7f985445d
        }



=======
            Car_tradege();
            //printf("%d\r\n",Car_State);
            printf("%d,%d,%d,%d,%d,%d\r\n",  offset, desired_speed_left, desired_speed_right ,left_speed,right_speed,Car_State);
            //printf("%d,%d,%d,%d,%d\r\n",left_lose,right_lose,Car_State,left_speed,right_speed);
            time0=0;
        }

        switch(Car_State)
        {
            case 0:
                Car_stop();
                break;
            case 1:
                base_speed=10;
                adjust_motor_speed(offset);
                break;
            case 2: //右环
                adjust_motor_speed(25);
                system_delay_ms(1500);
                Car_State=1;
                break;
            case 3:
                adjust_motor_speed(-25);
                system_delay_ms(1500);
                Car_State=1;
                break;
            case 4:
                base_speed=15;
                adjust_motor_speed(0);
                break;
            case 5:
                adjust_motor_speed(0);
                break;
        }
>>>>>>> Stashed changes
//        printf(
//            "ADC channel %d mean filter convert data is %d.\r\n",
//            1,
//            adc_result );      // 循环输出 10 次均值滤波转换结果
            //printf("offset:%d\r\n",offset_adc);
            //time=0;

        // �˴���д��Ҫѭ��ִ�еĴ���
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
    }
}
#pragma section all restore


// **************************** 代码区域 ****************************
