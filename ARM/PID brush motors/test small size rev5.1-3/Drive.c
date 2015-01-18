#include "lpc17xx.h"
#include "pwm.h"
#include "delay.h"
#include "Drive.h"
#include "timer.h"
#include "EXTI.h"
#include "defines.h"

//int M1Time=0xFFFF;
//int M2Time=0xFFFF;
//int M3Time=0xFFFF;
//int M4Time=0xFFFF;

 
signed int m1;
signed int m2;
signed int m3;
signed int m4;

void Drive (signed int m1,signed int m2,signed int m3,signed int m4)
{
	if ( m1>255 )
	{
		   m1=255;
	}
	else if ( m1<-255 )
	{
		   m1=-255;
	}

	if ( m2>255 )
	{
		   m2=255;
	}
	else if ( m2<-255 )
	{
		   m2=-255;
	}

	if ( m3>255 )
	{
		   m3=255;
	}
	else if ( m3<-255 )
	{
		   m3=-255;
	}

	if ( m4>255 )
	{
		   m4=255;
	}
	else if ( m4<-255 )
	{
		   m4=-255;
	}
	


	if ( m1==0 )
		{
			LPC_GPIO2->FIOSET |= 0x20;
			LPC_PWM1->MR3 = 255;
		}
	else if ( m1>0 )
		{
			LPC_GPIO2->FIOSET |= 0x20;
			LPC_PWM1->MR3 = 255 - m1;
		}
	else if ( m1<0 )
		{
			LPC_GPIO2->FIOCLR |= 0x20;
			LPC_PWM1->MR3 = -m1;
		}

	if ( m2==0 )
		{
			LPC_GPIO0->FIOSET |= 0x8;
			LPC_PWM1->MR1 = 255;
		}
	else if ( m2>0 )
		{
			LPC_GPIO0->FIOSET |= 0x8;
			LPC_PWM1->MR1 = 255 - m2;
		}
	else if ( m2<0 )
		{
			LPC_GPIO0->FIOCLR |= 0x8;
			LPC_PWM1->MR1 = -m2;
		}

	if ( m3==0 )
		{
			LPC_GPIO0->FIOSET |= 0x200;
			LPC_PWM1->MR2 = 255;
		}
	else if ( m3>0 )
		{
			LPC_GPIO0->FIOSET |= 0x200;
			LPC_PWM1->MR2 = 255 - m3;
		}
	else if ( m3<0 )
		{
			LPC_GPIO0->FIOCLR |= 0x200;
			LPC_PWM1->MR2 = -m3;
		}

	if ( m4==0 )
		{
			LPC_GPIO0->FIOSET |= 0x10000;
			LPC_PWM1->MR4 = 255;
		}
	else if ( m4>0 )
		{
			LPC_GPIO0->FIOSET |= 0x10000;
			LPC_PWM1->MR4 = 255 - m4;
		}
	else if ( m4<0 )
		{
			LPC_GPIO0->FIOCLR |= 0x10000;
			LPC_PWM1->MR4 = -m4;
		}

	  
	  LPC_PWM1->LER |= LER2_EN;
	  LPC_PWM1->LER |= LER4_EN;
	  LPC_PWM1->LER |= LER3_EN;
	  LPC_PWM1->LER |= LER1_EN;
}



