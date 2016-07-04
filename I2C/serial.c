#include "serial.h"
#include "init.h"

#define TXD0READY   (1<<2)

void uart_init(void)
{
	GPHCON  |= 0xa0;    // GPH2,GPH3用作TXD0,RXD0
	GPHUP   = 0x0c;     // GPH2,GPH3内部上拉

	ULCON0  = 0x03;     // 8N1(8个数据位，无较验，1个停止位)
	UCON0   = 0x05;     // 查询方式，UART时钟源为PCLK
	UFCON0  = 0x00;     // 不使用FIFO
	UMCON0  = 0x00;     // 不使用流控
	UBRDIV0 = UART_BRD; // 波特率为115200
}

/*
 * 发送一个字符
 */
void putc(unsigned char c)
{
    /* 等待，直到发送缓冲区中的数据已经全部发送出去 */
    while (!(UTRSTAT0 & TXD0READY));

    /* 向UTXH0寄存器中写入数据，UART即自动将它发送出去 */
    UTXH0 = c;
}

/*
 * 接收字符
 */
unsigned char getc(void)
{
    /* 等待，直到接收缓冲区中的有数据 */
    while (!(UTRSTAT0 & RXD0READY));

    /* 直接读取URXH0寄存器，即可获得接收到的数据 */
    return URXH0;
}
