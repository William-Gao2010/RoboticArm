#include <STC8G.H>
#include <intrins.h>
#define u8 unsigned char
#define u16 unsigned int
sbit key1=P3^3;
sbit key_L=P3^1;
u8 adc_x,adc_y,keep;
void IOOPEN()
{
		P1M0 = 0x00; P1M1 = 0x03;
		P3M0 = 0x00; P3M1 = 0x00;
		P5M0 = 0x00; P5M1 = 0x00;
}
void Uart1_Init(void)	//9600bps@35.000MHz
{
		EA=1;
		ES=1;
		SCON = 0x50;
		AUXR |= 0x40;
		AUXR &= 0xFE;
		TMOD &= 0x0F;
		TL1 = 0x71;
		TH1 = 0xFC;
		ET1 = 0;
		TR1 = 1;
}
void Delay1ms(u16 t)	//@35.000MHz
{
	unsigned char data i, j;
	while(t--)
	{
			_nop_();
			_nop_();
			i = 46;
			j = 113;
			do
			{
				while (--j);
			} while (--i);
	}
}
void sending(u8 byte)
{
		SBUF=byte;
		while(!TI);
    TI = 0;
}
void ADOPEN()
{
		P_SW2|=0X80;
		ADCTIM=0X2A;
		P_SW2&=0X7F;
		ADCCFG=0X2F;
		ADC_CONTR=0X80;
}
u16 adcread(u8 adcin)
{
		ADC_CONTR=0xC0|adcin;
		_nop_();
		_nop_();
		while(!(ADC_CONTR & 0X20));
		ADC_CONTR&=~0X20;
		return (ADC_RES<<2)|ADC_RESL;
}
void Init() interrupt 4
{
		if(TI)
		{
				TI=0;
		}
		if(RI)
		{
				RI=0;
		}
}