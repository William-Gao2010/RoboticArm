#include <STC8H.H>
#include <intrins.h>
#include <LC12S.h>
#include <PWM.c>


#define true 1
#define false 0

sbit laser = P3^3;

unsigned char DegreeData[3];
unsigned char num1;



void check()
{
		for(num1=0;num1<6;num1++)
		{
				if((temp[num1]==0x91) & (temp[num1+4]==0x78))
				{
						number[0]=temp[num1];
						number[1]=temp[num1+1];
						number[2]=temp[num1+2];
						number[3]=temp[num1+3];
						number[4]=temp[num1+4];
						break;
				}
		}
}

void UrtlInit()
{
	 P_SW1=0x40;
	REN=1;
	Delay1ms(150);
	P_SW1=0x00;
	REN=0;
	check();
}

void SendRecieveData()
{
	unsigned char i;
	for(i=0;i<5;i++)
	{
			sending(number[i]);
			Delay1ms(10);
	}
}

void x()
{
		if((number[3]>0x0a)){DegreeData[0]+=5;	number[3]=(number[3]-0x7f);}
		if(DegreeData[0]>0x80)DegreeData[0]=0x82;
		if((number[3]<0x0a)){DegreeData[0]-=5;	number[3]=(0x7f-number[3]);}
		if(DegreeData[0]<0x26)DegreeData[0]=0x21;
}

void y()
	{
		if((number[2]>0x08)){DegreeData[1]+=5;DegreeData[2]-=5;number[2]=(number[2]-0x7f);}
		if(DegreeData[1]>0x80){DegreeData[1]=0x82;DegreeData[2]=0x21;}
		if((number[2]<0x08)){DegreeData[1]-=5;DegreeData[2]+=5;number[2]=(0x7f-number[2]);}
		if(DegreeData[1]<0x26){DegreeData[1]=0x21;DegreeData[2]=0x82;}
}
	


bit blank()
{
		unsigned char num4;
		for(num4=0;num4<5;num4++)
				if(number[num4])
						return true;
		return false;
}

void DimensionsCheck()
{
	 if(blank())
	 {
			x(); y();
	 }
}

void main()
{
        IoInit();
        Uart1_Init();
				Pwm_Init();
        while(1)
        {
						 UrtlInit();
						 check();
						 SendRecieveData();
						 DimensionsCheck();
						 run(DegreeData);
						 laser=number[0];
							run(DegreeData);
        }
}
