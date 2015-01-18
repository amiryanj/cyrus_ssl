#include "lpc17xx.h"
#include "pwm.h"
#include "defines.h"

//#define MAX_DUTY 256 // Maximum duty cycle for PWMs

volatile uint32_t match_counter0, match_counter1;

/******************************************************************************
** Function name:		PWM_Init
**
** Descriptions:		PWM initialization, setup all GPIOs to PWM0~6,
**				reset counter, all latches are enabled, interrupt
**				on PWMMR0, install PWM interrupt to the VIC table.
**
** parameters:			ChannelNum, Duty cycle
** Returned value:		true or fase, if VIC table is full, return false
** 
******************************************************************************/
void PWM_Init(void)
{

	LPC_SC->PCONP |= (1<<6); 			//Powers on the PWM 
	LPC_PINCON->PINSEL4  |= 0x00000555;	//set GPIOs fo PWM  PORT2 - PIN 0 -->6 
	LPC_PINCON->PINMODE4 |= 0x00000AAA;	//Pullups disabled for pwm pins
	
	LPC_PWM1->TCR = 2;                  // bring PWM module into reset
  
  	LPC_PWM1->IR = 0xff;				//Clears any pending interrupt 
	LPC_PWM1->PR = 0x61;				/* count frequency:Fpclk    25Mh z /(767+1)=32kHz*/
	LPC_PWM1->MCR = 0x2;				//Resets TC on MR0
	// set PWM cycle 
	LPC_PWM1->MR0 = 256;
	LPC_PWM1->MR1 = 0;
	LPC_PWM1->MR2 = 0;
	LPC_PWM1->MR3 = 0;
	LPC_PWM1->MR4 = 0;
	LPC_PWM1->MR5 = 0;
	LPC_PWM1->MR6 = 0;	

	/* all PWM latch enabled */
	//LPC_PWM1->LER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;

	PWM_Start();


}

/******************************************************************************
** Function name:		PWM_Set
**
** Descriptions:		PWM cycle setup
**
** parameters:			Channel number, PWM cycle, and offset
** Returned value:		None
** 
******************************************************************************/
void PWM_Set(uint32_t cycle)
{			
//	LPC_PWM1->MR0 = cycle;		/* set PWM cycle */
	LPC_PWM1->MR1 = cycle ;
	LPC_PWM1->MR2 = cycle * 2/3;
	LPC_PWM1->MR3 = cycle * 1/2;
	LPC_PWM1->MR4 = cycle * 1/3;
	LPC_PWM1->MR5 = cycle;
	LPC_PWM1->MR6 = cycle;

	/* The LER will be cleared when the Match 0 takes place, in order to
	load and execute the new value of match registers, all the PWMLERs need to
	reloaded. all PWM latch enabled */
	LPC_PWM1->LER = LER0_EN + LER1_EN + LER2_EN + LER3_EN + LER4_EN + LER5_EN + LER6_EN;
}

/******************************************************************************
** Function name:		PWM_Start
**
** Descriptions:		Enable PWM by setting the PCR, PTCR registers
**
** parameters:			channel number
** Returned value:		None
** 
******************************************************************************/
void PWM_Start()
{

	/* All single edge, all enable */
	LPC_PWM1->PCR = PWMENA1 | PWMENA2 | PWMENA3 | PWMENA4 | PWMENA5 | PWMENA6;
	LPC_PWM1->TCR = TCR_CNT_EN | TCR_PWM_EN;	/* counter enable, PWM enable */
}



/******************************************************************************
**                            End Of File
******************************************************************************/
