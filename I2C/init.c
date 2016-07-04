/******************************************************************************
 * init.c
 * init function
 *
 ******************************************************************************/

#include "init.h"

void disable_watch_dog(void)
{
	WTCON = 0;
}

/*
 * for MPLLCON register(main PLL control)，MDIV:19:12, PDIV: 9:4, SDIV:1:0
 *
 * set MPLLCON:
 * JZ2440，Fin = 12MHz
 * MPLL(FCLK) = (2 * m * Fin)/(p * 2^s)
 *   m = MDIV + 8, p = PDIV + 2, s = SDIV
 *
 * set CLKDIVN:
 * FCLK=200MHz,HCLK=100MHz,PCLK=50MHz
 * FCLK:HCLK:PCLK = 1:2:4
 */
#define FCLK        200000000
#define HCLK        100000000
#define PCLK        50000000
void clock_init(void)
{
	LOCKTIME = 0xFFFFFFFF; //default value
	CLKDIVN = 0x03;//FCLK:HCLK:PCLK = 1:2:4 no need set CAMDIVN, HDIVN=1,PDIVN=1

	__asm__(									/* if HDIVN is not 0,change fast bus mode to asynchronous bus mode*/
	    "mrc    p15, 0, r1, c1, c0, 0\n"        /* 读出控制寄存器 */
	    "orr    r1, r1, #0xc0000000\n"          /* 设置为“asynchronous bus mode” */
	    "mcr    p15, 0, r1, c1, c0, 0\n"        /* 写入控制寄存器 */
	    );

	MPLLCON = ( (0x2A<<12) | (0x01<<9) | 0x01 );//MDIV:42,PDIV:1,SDIV:1
}

void memsetup(void)
{
	volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;

	/* memory controller 13 register value */
	p[0] = 0x22011110;     //BWSCON            | 0010 | 0010 | XXXX | XXXX | XXXX | XXXX | XXXX | 0000 |
	p[1] = 0x00000700;     //BANKCON0
	p[2] = 0x00000700;     //BANKCON1
	p[3] = 0x00000700;     //BANKCON2
	p[4] = 0x00000700;     //BANKCON3
	p[5] = 0x00000700;     //BANKCON4
	p[6] = 0x00000700;     //BANKCON5
											/* | XXXX | XXXX | XXXX | XXX1 | 1XXX | XXXX | XXXX | 0101 |
											 * [16,15]:MT       11      Memory Type
											 * [3,2]:Trcd       01      RAS to CAS delay
											 * [0,1]SCAN        01      SDRAM列地址位数，九位
											 */
	p[7] = 0x00018005;     //BANKCON6
	p[8] = 0x00018005;     //BANKCON7

											/* REFRESH,
										     * | XXXX | XXXX | 1000 | 11XX | XXXX | XXXX | XXXX | XXXX |
										     * [23]:REFEN    		1          enable REFEN
										     * [22]:TFREMD   		0          CBR/auto refresh
										     * [21,20]:Trp   		00         SDRAM RAS per-change time
										     * [19,18]:Tsrc  		11         SDRAM Semi Raw Circle Type
										     * [10,0]: R_CNT 		value      Refresh Counter
										     * R_CNT = 2^11 + 1 - HCLK(MHz) * SDRAM fresh period
										     * HCLK=12MHz:  0x008C07A3
											 * HCLK=100MHz: 0x008C04F4
											 */
	p[9]  = 0x008C04F4;
	p[10] = 0x000000B1;     //BANKSIZE
	p[11] = 0x00000030;     //MRSRB6
	p[12] = 0x00000030;     //MRSRB7
}

void copy_steppingstone_to_sdram(void)
{
    unsigned int *pdwSrc  = (unsigned int *)0;
    unsigned int *pdwDest = (unsigned int *)0x30000000;

    while (pdwSrc < (unsigned int *)4096)
    {
        *pdwDest = *pdwSrc;
        pdwDest++;
        pdwSrc++;
    }
}
