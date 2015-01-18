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

	match_counter1 = 0;
	LPC_PINCON->PINSEL4 |= 0x00000055;	// set GPIOs for all PWM pins on PWM1  1 to 4
	LPC_PINCON->PINSEL3 |= 0x00220000;	//set GPIOs fo PWM 

	LPC_PWM1->TCR = TCR_RESET;	/* Counter Reset */ 
	LPC_PWM1->PR = 0x02;		/* count frequency:Fpclk */
	LPC_PWM1->MCR = PWMMR0I;	/* interrupt on PWMMR0, reset on PWMMR0, reset 
								TC if PWM1 matches */				
	LPC_PWM1->MR0 = MAX_DUTY + 1;		// set PWM cycle 
	LPC_PWM1->MR1 = 0;
	LPC_PWM1->MR2 = 0;
	LPC_PWM1->MR3 = 0;
	LPC_PWM1->MR4 = 0;
	LPC_PWM1->MR5 = 0;
	LPC_PWM1->MR6 = 0;	

	/* all PWM latch enabled */
	LPC_PWM1->LER = LER0_EN & LER1_EN & LER2_EN & LER3_EN & LER4_EN & LER5_EN & LER6_EN;

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
	LPC_PWM1->LER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;
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
