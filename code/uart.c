#include "zf_common_headfile.h"

uint8_t uart_get_data[64];                                                        // 串口接收数据缓冲区
uint8_t fifo_get_data[64];                                                        // fifo 输出读出缓冲区

uint8_t  get_data = 0;                                                            // 接收数据变量
uint32_t fifo_data_count = 0;                                                     // fifo 数据个数

fifo_struct uart_data_fifo;

void Uart_init(void)
{
    fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // 初始化 fifo 挂载缓冲区

    uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);             // 初始化串口
    uart_rx_interrupt(UART_INDEX, 1);                                           // 开启 UART_INDEX 的接收中断

    uart_write_string(UART_INDEX, "UART Text.");                                // 输出测试信息
    uart_write_byte(UART_INDEX, '\r');                                          // 输出回车
    uart_write_byte(UART_INDEX, '\n');                                          // 输出换行
}