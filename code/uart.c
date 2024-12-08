#include "zf_common_headfile.h"
                                                       // fifo 杈撳嚭璇诲嚭缂撳啿鍖�
uint8 uart_get_data[64];
uint8_t  get_data = 0;                                                            // 鎺ユ敹鏁版嵁鍙橀噺
uint32_t fifo_data_count = 0;                                                     // fifo 鏁版嵁涓暟
fifo_struct uart_data_fifo;
// 杈撳嚭鎹㈣
void Uart_init(void)
{           // 鍒濆鍖� fifo 鎸傝浇缂撳啿鍖�
    uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);             // 鍒濆鍖栦覆鍙�
    uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);
    uart_rx_interrupt(UART_INDEX, 1);                                           // 寮�鍚� UART_INDEX 鐨勬帴鏀朵腑鏂�
    fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // 初始化 fifo 挂载缓冲区
    uart_write_string(UART_INDEX, "UART Text.");                                // 杈撳嚭娴嬭瘯淇℃伅
    uart_write_byte(UART_INDEX, '\r');                                          // 杈撳嚭鍥炶溅
    uart_write_byte(UART_INDEX, '\n');
}

