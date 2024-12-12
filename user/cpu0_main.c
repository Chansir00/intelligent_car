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
int temp =0;
int offset_test = -250;
extern int left_speed ;
extern int right_speed ;
extern int base_speed;
int orin = 0;
int flag =0;

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

        time0++;
        // �˴���д��Ҫѭ��ִ�еĴ���
        //time++;
        if(time0==20)
        {
            key_scanner();
            // 处理按键动作
            process_key_actions();
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
//        printf(
//            "ADC channel %d mean filter convert data is %d.\r\n",
//            1,
//            adc_result );      // 循环输出 10 次均值滤波转换结果
            //printf("offset:%d\r\n",offset_adc);
            //time=0;

        // �˴���д��Ҫѭ��ִ�еĴ���

    }
}
#pragma section all restore


// **************************** 代码区域 ****************************
