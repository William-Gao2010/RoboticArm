#include <STC8H.H>
#include <stdlib.h>

void Delay1ms(int ms)	//@35MHz
{
	unsigned char data i, j;
	while(ms--)
	{
		i = 35;
		j = 8;
		do
		{
			while (--j);
		} while (--i);
	}
} 


void Pwm_Init(void)
{
	P_SW2=EAXFR; //????????(XFR)???????
	PWMA_PS = 0x00;//????PWMA???????§Ý?
	PWMB_PS = 0x55;//????PWMB???????§Ý?
	PWMA_CCER1 = 0x00; //§Õ CCMRx ??????????? CCxE ??????
	PWMA_CCER2 = 0x00;
	PWMB_CCER1 = 0x00;
	PWMB_CCER2 = 0x00;
	PWMA_CCMR1 = 0x60;
	PWMA_CCMR2 = 0x60;
	PWMA_CCMR3 = 0x60;
	PWMA_CCMR4 = 0x60;
	PWMB_CCMR1 = 0x60;
	PWMB_CCMR2 = 0x60;
	PWMB_CCMR3 = 0x60;
	PWMB_CCMR4 = 0x60;
	PWMA_CCER1 = 0x11;
	PWMA_CCER2 = 0x11;
	PWMB_CCER1 = 0x11;

	PWMB_CCER2 = 0x11;
	PWMA_CCMR1 = 0x68;
	PWMA_CCMR2 = 0x68;
	PWMA_CCMR3 = 0x68;
	PWMA_CCMR4 = 0x68;
	PWMB_CCMR1 = 0x68;
	PWMB_CCMR2 = 0x68;
	PWMB_CCMR3 = 0x68;
	PWMB_CCMR4 = 0x68;
	PWMA_PSCRH = 0x00;
	PWMA_PSCRL = 0x0b;
	PWMA_ARRH = 0xe3;
	PWMA_ARRL = 0xdd;
	PWMB_PSCRH = 0x00;
	PWMB_PSCRL = 0x0b;
	PWMB_ARRH = 0xe3;
	PWMB_ARRL = 0xdd;
	PWMA_CCR1H = 0x06;
	PWMA_CCR1L = 0xd6;
	PWMA_CCR2H = 0x06;
	PWMA_CCR2L = 0xd6;
	PWMA_CCR3H = 0x06;
	PWMA_CCR3L = 0xd6;
	PWMA_CCR4H = 0x06;
	PWMA_CCR4L = 0xd6;
	PWMB_CCR5H = 0x06;
	PWMB_CCR5L = 0xd6;
	PWMB_CCR6H = 0x06;
	PWMB_CCR6L = 0xd6;
	PWMB_CCR7H = 0x06;
	PWMB_CCR7L = 0xd6;
	PWMB_CCR8H = 0x06;
	PWMB_CCR8L = 0xd6;
	PWMA_ENO = 0x55;//????PWMA????????
	PWMB_ENO = 0x55;//????PWMB????????
	PWMA_BKR = 0x80;  //????????
	PWMA_CR1 = 0x01; //???ARR????,??????
	PWMB_BKR = 0x80;
	PWMB_CR1 = 0x01;
}

void UpdatePwm(unsigned char num, unsigned int duty_D)					//duty_D?????*1000
{
	unsigned int duty;
	duty=duty_D*58.333;
	if(num<=3&&duty>58333)return;// dutya?????????58333
	if(num>=4&&duty>58333)return;// dutyb?????????58333
	switch (num)
	{
		case 1:
			PWMA_CCR1H = (unsigned char)(duty >> 8); // ???????????
			PWMA_CCR1L = (unsigned char)(duty);
			break;
		case 2:
			PWMA_CCR2H = (unsigned char)(duty >> 8); // ???????????
			PWMA_CCR2L = (unsigned char)(duty);
			break;
		case 3:
			PWMA_CCR3H = (unsigned char)(duty >> 8); // ???????????
			PWMA_CCR3L = (unsigned char)(duty);
			break;
		case 4:
			PWMA_CCR4H = (unsigned char)(duty >> 8); // ???????????
			PWMA_CCR4L = (unsigned char)(duty);
			break;
		case 5:
			PWMB_CCR5H = (unsigned char)(duty >> 8); // ???????????
			PWMB_CCR5L = (unsigned char)(duty);
			break;
		case 6:
			PWMB_CCR6H = (unsigned char)(duty >> 8); // ???????????
			PWMB_CCR6L = (unsigned char)(duty);
			break;
		case 7:
			PWMB_CCR7H = (unsigned char)(duty >> 8); // ???????????
			PWMB_CCR7L = (unsigned char)(duty);
			break;
		case 8:
			PWMB_CCR8H = (unsigned char)(duty >> 8); // ???????????
			PWMB_CCR8L = (unsigned char)(duty);
			break;
		default:
			break;
	}
}


void run(unsigned char *Arri)
{
	UpdatePwm(1,Arri[0]);
	Delay1ms(number[3]);
	UpdatePwm(2,Arri[1]);
	UpdatePwm(3,(180-Arri[1]));
	Delay1ms(number[3]);
	UpdatePwm(4,Arri[2]);
	Delay1ms(number[2]);
	UpdatePwm(5,Arri[2]);
	Delay1ms(number[2]);
}
