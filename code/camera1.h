/*
 * camera1.h
 *
 *  Created on: 2024年11月6日
 *      Author: 64271
 */

#ifndef CAMERA1_H
#define CAMERA1_H

#include <stdint.h>

struct LEFT_EDGE {
    int16_t row;  // 琛屽潗鏍�
    int16_t col;  // 鍒楀潗鏍�
    uint8_t flag; // 瀛樺湪杈圭晫鐨勬爣蹇�
};

struct RIGHT_EDGE {
    int16_t row;  // 琛屽潗鏍�
    int16_t col;  // 鍒楀潗鏍�
    uint8_t flag; // 瀛樺湪杈圭晫鐨勬爣蹇�
};
struct CENTRE {
    int16_t row;  // 琛屽潗鏍�
    int16_t col;  // 鍒楀潗鏍�
    uint8_t flag; // 瀛樺湪杈圭晫鐨勬爣蹇�
};

// 鍥惧儚灏哄
#define IMAGE_H    120 // 鍥惧儚楂樺害
#define IMAGE_W    160 // 鍥惧儚瀹藉害
#define GrayScale 256

// 鍏ㄥ眬鍙橀噺澹版槑
extern struct LEFT_EDGE L_edge[140];
extern struct RIGHT_EDGE R_edge[140];
extern struct CENTRE Centre[140];
extern uint8_t L_edge_count, R_edge_count;
extern uint8_t dire_left, dire_right;
extern uint8_t L_search_amount, R_search_amount;
extern uint16_t L_corner_flag, L_corner_row, L_corner_col;
extern uint16_t L_corner_angle;
extern uint16_t R_corner_flag, R_corner_row, R_corner_col;
extern uint16_t R_corner_angle;
extern uint16_t enable_L_corner, enable_R_corner;
extern uint8_t Image_use_zip[IMAGE_H][IMAGE_W];
extern uint8_t Image_use_out[IMAGE_H][IMAGE_W];
// 鍑芥暟澹版槑

/**
 * @brief 蹇�熷ぇ娲�
 * @param image 鍘熷鍥惧儚鏁版嵁
 * @return 璁＄畻寰楀埌鐨勯槇鍊�
 * @since v1.1
 * @note Example: uint8_t OTSU_Threshold = otsuThreshold(mt9v03x_image_dvp[0]);
 */
uint8_t otsuThreshold1(uint8_t *image);

/**
 * @brief 鍥惧儚鍘嬬缉
 * @return void
 * @since v2.0
 * @note Example: void compressimage();
 */
void compressimage(void);

/**
 * @brief Soble鍥哄畾闃堝��
 * @param imageIn 杈撳叆鍥惧儚
 * @param imageOut 杈撳嚭鍥惧儚
 * @param Threshold 闃堝��
 * @return void
 * @since v1.2
 * @note Example: sobel(Image_use_zip, Image_use, 60);
 */
void sobel(uint8_t imageIn[IMAGE_H][IMAGE_W], uint8_t imageOut[IMAGE_H][IMAGE_W], uint8_t Threshold);

/**
 * @brief 缁欏浘鍍忕敾榛戞涓哄叓閭诲煙鍋氬噯澶�
 * @param image 杈撳叆鍥惧儚
 * @return void
 * @since v1.0
 * @note Example: image_draw_rectan(Image_use);
 */
void image_draw_rectan1(uint8_t image[IMAGE_H][IMAGE_W]);

/**
 * @brief 鍏偦鍩熸壘杈圭晫
 * @return void
 * @note Example: search_neighborhood();
 */
void search_neighborhood(void);

/**
 * @brief 鍏偦鍩熻竟鐣屽垵濮嬪寲
 * @return void
 * @note Example: clear_find_point();
 */
void clear_find_point(void);

/**
 * @brief 宸瘮鍜�
 * @param x 杈撳叆鍊紉
 * @param y 杈撳叆鍊紋
 * @return 璁＄畻缁撴灉
 * @note Example: int16_t diff = calc_diff(x, y);
 */
uint16_t calc_diff(uint16_t x, uint16_t y);

/**
 * @brief 鎷愮偣妫�娴�
 * @return void
 * @note Example: get_turning_point();
 */
void get_turning_point(void);

/**
 * @brief 閫嗛�忚鐭ヤ笁鐐规眰褰㈡垚鐨勮搴�
 * @param Ax 涓嬭竟鐐箈鍧愭爣
 * @param Ay 涓嬭竟鐐箉鍧愭爣
 * @param Bx 瑕佹眰瑙掑害鐨勪竴鐐箈鍧愭爣
 * @param By 瑕佹眰瑙掑害鐨勪竴鐐箉鍧愭爣
 * @param Cx 涓婅竟鐐箈鍧愭爣
 * @param Cy 涓婅竟鐐箉鍧愭爣
 * @return 璁＄畻寰楀埌鐨勮搴�
 * @since v1.0
 * @note Example: float angle = Get_angle(Ax, Ay, Bx, By, Cx, Cy);
 */
float Get_angle(float Ax, float Ay, float Bx, float By, float Cx, float Cy);

/**
 * @brief 闄愬箙
 * @param x 琚檺骞呯殑鏁版嵁
 * @param y 闄愬箙鑼冨洿(鏁版嵁浼氳闄愬埗鍦�-y鑷�+y涔嬮棿)
 * @return 闄愬箙涔嬪悗鐨勬暟鎹�
 * @note Example: float dat = limit(500, 300);
 */
float limit(float x, uint32_t y);

// 缁撴瀯浣撳０鏄�


uint8_t Deal_img(void);


int calculate_offset(void);


void adjust_motor_speed();

void update_mid_line_array(void);

#endif // CAMERA1_H
