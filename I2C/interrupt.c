#include <stdio.h>
#include "init.h"
#include "interrupt.h"
#include "i2c.h"

void (*isr_handle_array[50])(void);//函数指针数组

void Dummy_isr(void)
{
    printf("Dummy_isr\n\r");
    while(1);
}

void init_irq(int void)
{
	int i = 0;

	for (i = 0; i < (sizeof(isr_handle_array) / sizeof(isr_handle_array[0])); i++)
	{
		isr_handle_array[i] = Dummy_isr;
	}

	INTMOD = 0x0;	      // 所有中断都设为IRQ模式
	INTMSK = BIT_ALLMSK;  // 先屏蔽所有中断

	isr_handle_array[ISR_IIC_OFT]  = I2CIntHandle;//27
}
