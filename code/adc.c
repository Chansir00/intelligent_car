/*
 * adc.c
 *
 *  Created on: 2024骞�11鏈�25鏃�
 *      Author: 闂竵鐞�
 */

#include "zf_common_headfile.h"

void adc_ini()
{
    adc_init(ADC_CHANNEL1, ADC_8BIT);                                          // 鍒濆鍖栧搴� ADC 閫氶亾涓哄搴旂簿搴�
    adc_init(ADC_CHANNEL2, ADC_8BIT);                                          // 鍒濆鍖栧搴� ADC 閫氶亾涓哄搴旂簿搴�
    adc_init(ADC_CHANNEL3, ADC_8BIT);                                          // 鍒濆鍖栧搴� ADC 閫氶亾涓哄搴旂簿搴�
    adc_init(ADC_CHANNEL4, ADC_8BIT);                                           // 鍒濆鍖栧搴� ADC 閫氶亾涓哄搴旂簿搴�
}


// 归一化函数
float normalize(int adc_value, int adc_max) {
    return (float)adc_value / adc_max;
}

// 差比和计算函数
float calculate_differential_ratio(float V1_norm, float V2_norm) {
    if (V1_norm + V2_norm != 0) {
        return (V1_norm - V2_norm) / (V1_norm + V2_norm);
    } else {
        return 0;  // 避免除以 0
    }
}
//void AD_filter(int offset)
//{
//
//}
