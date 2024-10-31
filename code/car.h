#ifndef CAR_H
#define CAR_H

#define UART_INDEX              (DEBUG_UART_INDEX   )                           // 默认 UART_0
#define UART_BAUDRATE           (DEBUG_UART_BAUDRATE)                           // 默认 115200
#define UART_TX_PIN             (DEBUG_UART_TX_PIN  )                           // 默认 UART0_TX_P14_0
#define UART_RX_PIN             (DEBUG_UART_RX_PIN  )                           // 默认 UART0_RX_P14_1


typedef enum {
    STOP,
    STREIGHT,
    LEFT,
    RIGHT,
    LEFT_CIRCLE,
    RIGHT_CIRCLE
} car_direction;

void Car_stop(void);
void Car_streight(void);
void Car_left(void);
void Car_right(void);
void Car_left_circle(void);
void Car_right_circle(void);
void kernel(void);
void Car_Init(void);
void Car_go(void);

#endif
