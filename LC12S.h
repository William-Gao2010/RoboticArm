#include <STC8H.H>
#include <intrins.h>

unsigned char tmp;
unsigned char num;
unsigned char temp[10];
unsigned char number[5];

void IoInit()
{
        P1M0 = 0x00; P1M1 = 0x00;
        P3M0 = 0x00; P3M1 = 0x00;
        P5M0 = 0x00; P5M1 = 0x00;
}
void Uart1_Init(void)    //9600bps@35.000MHz
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
void sending(unsigned char byte)
{
        SBUF=byte;
        while(TI);
        TI=0;
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
                num=SBUF;
                temp[tmp]=num;
                if(tmp==9)
                {
                        tmp=0;
                        REN=0;
                }
                                tmp++;
        }
}

