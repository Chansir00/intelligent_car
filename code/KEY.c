#include "zf_common_headfile.h"
extern uint8_t Run;          // 杞︾姸鎬�,0:鍋滆溅,1:姝ｅ父
extern int offset_test;
extern int base_speed;
extern float kp_steer;
uint8_t debug = 0;
// 示例的按键处理函数


void handle_key_1_short_press(void) {
    uart_write_string(UART_INDEX, "Start");
    Run=1;

}


void handle_key_2_short_press(void) {
     uart_write_string(UART_INDEX, "Test");
     base_speed=6;
     kp_steer = 0.1;   //line=100


}

void handle_key_3_short_press(void) {
     uart_write_string(UART_INDEX, "stop");
     base_speed=10;
     kp_steer = 0.08;
}


// 其他按键的处理函数...

void process_key_actions(void)
{
    for (uint8_t i = 0; i < KEY_NUMBER; i++)
    {
        key_state_enum state = key_get_state(i);

        switch (state)
        {
            case KEY_SHORT_PRESS:
                // 短按处理
                switch (i)
                {
                    case KEY_1:
                        handle_key_1_short_press();
                        break;
                    case KEY_2:
                        handle_key_2_short_press();
                        break;
                    case KEY_3:
                        handle_key_3_short_press();
                        break;
                    // 根据需要添加更多按键的处理
                    default:
                        break;
                }
                break;

            // case KEY_LONG_PRESS:
            //     // 长按处理
            //     switch (i)
            //     // {
            //     //     case KEY_1:
            //     //         handle_key_1_long_press();
            //     //         break;
            //     //     case KEY_2:
            //     //         handle_key_2_long_press();
            //     //         break;
            //     //     // 根据需要添加更多按键的处理
            //         default:
            //             break;
            //     }
            //     break;

            // default:
            //     break;
        }

        // 清除按键状态
        key_clear_state(i);
    }
}


