/*
 * tft.c
 *
 *  Created on: 2024��11��1��
 *      Author: 64271
 */
#include "zf_common_headfile.h"



//���Ʊ��ߺ��������߼����ܶ���㣩
void Find_Mid_Line_Draw_Line(void)
{
    uart_write_byte (UART_INDEX,L_edge[60].col);
    uart_write_byte (UART_INDEX,R_edge[60].col);
    for(uint16_t i = MT9V03X_H - 1; i > 0;i--)
    {
        //ȫ��
        draw_points(L_edge[i].col,L_edge[i].row,RGB565_BLACK );
        draw_points(R_edge[i].col,L_edge[i].row,RGB565_BLACK );
        draw_points(Centre[i].col,Centre[i].row,RGB565_BLACK );
    }
}

//�Ź��񻭵㺯��
//�ھŹ����ߵ�ͬʱҪע�����鲻��Խ�磬���ж��Ƿ�Ϊ�߽�㣬����Щ���Ǳ߽��Ͳ��ܻ���
// �Ź��񻭵㺯���Ľ�
void draw_points(uint16_t x, uint16_t y, uint16_t color)
{
    if (x < MT9V03X_W - 1) // ����Ƿ񳬳��ұ߽�
    {
        tft180_draw_point(x + 1, y, color);
        if (y < MT9V03X_H - 1) // ����Ƿ񳬳��±߽�
        {
            tft180_draw_point(x, y + 1, color);
            tft180_draw_point(x + 1, y + 1, color);
        }
        if (y > 0) // ����Ƿ񳬳��ϱ߽�
        {
            tft180_draw_point(x, y - 1, color);
            tft180_draw_point(x + 1, y - 1, color);
        }
    }
    if (x > 0) // ����Ƿ񳬳���߽�
    {
        tft180_draw_point(x - 1, y, color);
        if (y < MT9V03X_H - 1) // ����Ƿ񳬳��±߽�
        {
            tft180_draw_point(x, y + 1, color);
            tft180_draw_point(x - 1, y + 1, color);
        }
        if (y > 0) // ����Ƿ񳬳��ϱ߽�
        {
            tft180_draw_point(x, y - 1, color);
            tft180_draw_point(x - 1, y - 1, color);
        }
    }
    // �������ĵ�
    tft180_draw_point(x, y, color);
}



