#include <STC8G.H>
#include <intrins.h>
#include <LC12S.h>
void main()
{
		ADOPEN();
		Uart1_Init();
		IOOPEN();
		P_SW1=0x40;
		while(1)
		{
				while(key_L!=0);
				Delay1ms(500);
				while(key_L!=0)
				{ 
						adc_x=adcread(0x00);
						adc_y=adcread(0x01);
						
						sending(0x91);
						Delay1ms(10);
						
						sending(1);
						Delay1ms(10);
						
						if(key1!=0)
						{
								sending(adc_x);
								Delay1ms(10);
								
								sending(adc_y);
								keep=adc_y;
								Delay1ms(10);
						}
								
						if(key1==0)
						{
								sending(keep);
								Delay1ms(10);
							
								sending(adc_y);
								Delay1ms(10);
						}
						
						sending(0x78);
						Delay1ms(10);
				}
				
				while(key_L!=0);
				Delay1ms(500);
				while(key_L!=0)
				{
						adc_x=adcread(0x00);
						adc_y=adcread(0x01);
						
						sending(0x91);
						Delay1ms(10);
						
						sending(0);
						Delay1ms(10);
						
						if(key1!=0)
						{
								sending(adc_x);
								Delay1ms(10);
								
								sending(adc_y);
								keep=adc_y;
								Delay1ms(10);
						}
								
						if(key1==0)
						{
								sending(keep);
								Delay1ms(10);
								sending(adc_y);
								Delay1ms(10);
						}
						
						sending(0x78);
						Delay1ms(10);
				}
		}
}