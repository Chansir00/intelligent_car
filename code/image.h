/*
 * image.h
 *
 *  Created on: 2024��11��6��
 *      Author: 64271
 */

#ifndef _IMAGE_H
#define _IMAGE_H


//��������������������ֲ������ֲ��ʱ�����ɾ�����ĳ����Լ��ģ�
//typedef   signed          char int8;
//typedef   signed short     int int16;
//typedef   signed           int int32;
//typedef unsigned          char uint8;
//typedef unsigned short     int uint16;
//typedef unsigned           int uint32;

//��ɫ����  ��Ϊ������������ɫ���Ĳ�������ֱ�ӷ�����
#define uesr_RED     0XF800    //��ɫ
#define uesr_GREEN   0X07E0    //��ɫ
#define uesr_BLUE    0X001F    //��ɫ




//�궨��
#define image_h 120//ͼ��߶�
#define image_w 160//ͼ����

#define white_pixel 255
#define black_pixel 0

#define bin_jump_num    1//�����ĵ���
#define border_max  image_w-2 //�߽����ֵ
#define border_min  1   //�߽���Сֵ
extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];//ͼ������

extern void image_process(void); //ֱ�����жϻ�ѭ������ô˳���Ϳ���ѭ��ִ����

#endif /*_IMAGE_H*/

