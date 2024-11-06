/*
 * tft.c
 *
 *  Created on: 2024年11月1日
 *      Author: 64271
 */
#include "zf_common_headfile.h"



//绘制边线函数（画线即画很多个点）
void Find_Mid_Line_Draw_Line(void)
{
    uart_write_byte (UART_INDEX,L_edge[60].col);
    uart_write_byte (UART_INDEX,R_edge[60].col);
    for(uint16_t i = MT9V03X_H - 1; i > 0;i--)
    {
        //全画
        draw_points(L_edge[i].col,L_edge[i].row,RGB565_BLACK );
        draw_points(R_edge[i].col,L_edge[i].row,RGB565_BLACK );
        draw_points(Centre[i].col,Centre[i].row,RGB565_BLACK );
    }
}

//九宫格画点函数
//在九宫格画线的同时要注意数组不能越界，即判断是否为边界点，若有些点是边界点就不能画点
// 九宫格画点函数改进
void draw_points(uint16_t x, uint16_t y, uint16_t color)
{
    if (x < MT9V03X_W - 1) // 检查是否超出右边界
    {
        tft180_draw_point(x + 1, y, color);
        if (y < MT9V03X_H - 1) // 检查是否超出下边界
        {
            tft180_draw_point(x, y + 1, color);
            tft180_draw_point(x + 1, y + 1, color);
        }
        if (y > 0) // 检查是否超出上边界
        {
            tft180_draw_point(x, y - 1, color);
            tft180_draw_point(x + 1, y - 1, color);
        }
    }
    if (x > 0) // 检查是否超出左边界
    {
        tft180_draw_point(x - 1, y, color);
        if (y < MT9V03X_H - 1) // 检查是否超出下边界
        {
            tft180_draw_point(x, y + 1, color);
            tft180_draw_point(x - 1, y + 1, color);
        }
        if (y > 0) // 检查是否超出上边界
        {
            tft180_draw_point(x, y - 1, color);
            tft180_draw_point(x - 1, y - 1, color);
        }
    }
    // 绘制中心点
    tft180_draw_point(x, y, color);
}



