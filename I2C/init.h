/******************************************************************************
 * init.h
 ******************************************************************************/

#ifndef _INIT_H_
#define _INIT_H_

/* WATCH DOG register */
#define		WTCON           (*(volatile unsigned long *)0x53000000)
#define		WTDAT           (*(volatile unsigned long *)0x53000004)
#define 	WTCNT           (*(volatile unsigned long *)0x53000008)

/* CLOCK register */
#define 	LOCKTIME        (*(volatile unsigned long *)0x4C000000)
#define 	MPLLCON         (*(volatile unsigned long *)0x4C000004)
#define 	UPLLCON         (*(volatile unsigned long *)0x4C000008)//for USB
#define 	CLKDIVN         (*(volatile unsigned long *)0x4C000014)

/* SDRAM register */
#define 	MEM_CTL_BASE    0x48000000
#define 	SDRAM_BASE	    0x30000000

/* GPIO registers */
#define GPACON              (*(volatile unsigned long *)0x56000000)
#define GPADAT              (*(volatile unsigned long *)0x56000004)

#define GPBCON              (*(volatile unsigned long *)0x56000010)
#define GPBDAT              (*(volatile unsigned long *)0x56000014)
#define GPBUP               (*(volatile unsigned long *)0x56000018)

#define GPCCON              (*(volatile unsigned long *)0x56000020)
#define GPCDAT              (*(volatile unsigned long *)0x56000024)
#define GPCUP               (*(volatile unsigned long *)0x56000028)

#define GPDCON              (*(volatile unsigned long *)0x56000030)
#define GPDDAT              (*(volatile unsigned long *)0x56000034)
#define GPDUP               (*(volatile unsigned long *)0x56000038)

#define GPECON    			(*(volatile unsigned long *)0x56000040)
#define GPEDAT    		    (*(volatile unsigned long *)0x56000044)
#define GPEUP     			(*(volatile unsigned long *)0x56000048)

#define GPFCON              (*(volatile unsigned long *)0x56000050)
#define GPFDAT              (*(volatile unsigned long *)0x56000054)
#define GPFUP               (*(volatile unsigned long *)0x56000058)

#define GPGCON              (*(volatile unsigned long *)0x56000060)
#define GPGDAT              (*(volatile unsigned long *)0x56000064)
#define GPGUP               (*(volatile unsigned long *)0x56000068)

#define GPHCON              (*(volatile unsigned long *)0x56000070)
#define GPHDAT              (*(volatile unsigned long *)0x56000074)
#define GPHUP               (*(volatile unsigned long *)0x56000078)

/*UART registers*/
#define ULCON0              (*(volatile unsigned long *)0x50000000)
#define UCON0               (*(volatile unsigned long *)0x50000004)
#define UFCON0              (*(volatile unsigned long *)0x50000008)
#define UMCON0              (*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0            (*(volatile unsigned long *)0x50000010)
#define UTXH0               (*(volatile unsigned char *)0x50000020)
#define URXH0               (*(volatile unsigned char *)0x50000024)
#define UBRDIV0             (*(volatile unsigned long *)0x50000028)

/*interrupt registes*/
#define SRCPND              (*(volatile unsigned long *)0x4A000000)
#define INTMOD              (*(volatile unsigned long *)0x4A000004)
#define INTMSK              (*(volatile unsigned long *)0x4A000008)
#define PRIORITY            (*(volatile unsigned long *)0x4A00000c)
#define INTPND              (*(volatile unsigned long *)0x4A000010)
#define INTOFFSET           (*(volatile unsigned long *)0x4A000014)
#define SUBSRCPND           (*(volatile unsigned long *)0x4A000018)
#define INTSUBMSK           (*(volatile unsigned long *)0x4A00001c)


/* I2C registers */
#define IICCON  	(*(volatile unsigned *)0x54000000) // IIC control
#define IICSTAT 	(*(volatile unsigned *)0x54000004) // IIC status
#define IICADD  	(*(volatile unsigned *)0x54000008) // IIC address
#define IICDS   	(*(volatile unsigned *)0x5400000c) // IIC data shift
#define IICLC		(*(volatile unsigned *)0x54000010)	 //IIC multi-master line control

//pending bit
#define BIT_IIC				(0x1<<27)
#define BIT_ALLMSK			(0xffffffff)


#endif // _INIT_H_
