/*
 * adc.h
 *
 *  Created on: 2024骞�11鏈�25鏃�
 *      Author: 闂竵鐞�
 */

#ifndef CODE_ADC_H_
#define CODE_ADC_H_

#define ADC_MAX 255
#define ADC_MIN 0
#define CHANNEL_NUMBER          (4)
#define GET_AD 4
#define ADC_CHANNEL1            (ADC0_CH10_A10)
#define ADC_CHANNEL2            (ADC0_CH11_A11)  //1
#define ADC_CHANNEL3            (ADC0_CH12_A12)
#define ADC_CHANNEL4            (ADC0_CH13_A13) //4
void adc_ini();

void AD_get(void);
void AD_filter(int offset);
// 归一化函数
float normalize(int adc_value, int adc_max);


// 差比和计算函数
float calculate_differential_ratio(float V1_norm, float V2_norm,float V3_norm, float V4_norm);

#endif /* CODE_ADC_H_ */
