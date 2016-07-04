#include "init.h"
#include "i2c.h"
/*
 * I2C�жϷ������
 * ����ʣ������ݳ���ѡ�����������߽���
 */
void I2CIntHandle(void)
{

}

void i2c_init(void)
{
    GPEUP  |= 0xc000;       // ��ֹ�ڲ�����
    GPECON |= 0xa0000000;   // ѡ�����Ź��ܣ�GPE15:IICSDA, GPE14:IICSCL

    INTMSK &= ~(BIT_IIC);

    /* bit[7] = 1, ʹ��ACK
     * bit[6] = 0, IICCLK = PCLK/16
     * bit[5] = 1, ʹ���ж�
     * bit[3:0] = 0xf, Tx clock = IICCLK/16
     * PCLK = 50MHz, IICCLK = 3.125MHz, Tx Clock = 0.195MHz
     */
    IICCON = (1<<7) | (0<<6) | (1<<5) | (0xf);  // 0xaf

    IICADD  = 0x10;     // S3C24xx slave address = [7:1]
    IICSTAT = 0x10;     // I2C�������ʹ��(Rx/Tx)
}
static int test()
{
	while()
	{
		a = b;
		
	}
	while(1)
	{
	
	}
	while()
	{
		
	}
}
