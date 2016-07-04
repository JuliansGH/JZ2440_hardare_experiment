


#define NFCONF			(*(volatile unsigned long *)0x4E000000)
#define NFCONT 			(*(volatile unsigned long *)0x4E000004)
#define NFCMMD			(*(volatile unsigned long *)0x4E000008)
#define NFSTAT			(*(volatile unsigned long *)0x4E000020)


#define BUSY			(1)
/* 发出片选信号 */
static void nand_select_chip(void)
{
    int i = 0;

    NFCONT &= ~(1<<1);
    for(i=0; i<10; i++);
}

static void nand_write_cmd(int cmd)
{
	NFCMMD = cmd;
}

static void nand_wait_idle(void)
{
	int i = 0;

	while (!(NFSTAT & BUSY))
	{
		for (i=0; i<10; i++);
	}
}

static void nand_deselect_chip(void)
{
	NFCONT |= (1<<1);
}

static void nand_reset(void)
{
	nand_select_chip();
	nand_write_cmd();
	nand_wait_idle();
	nand_deselect_chip();
}

#define TACLS   0
#define TWRPH0  3
#define TWRPH1  0
void nand_init(void)
{
	/*set timer*/
	NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	/* Enable NAND Flash controller, init ECC, select chip:1  */
	NFCONT = (1<<4)|(1<<1)|(1<<0);

	nand_reset();
}
