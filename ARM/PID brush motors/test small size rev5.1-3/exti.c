#include <LPC17xx.h>
#include "exti.h"
void EXTI_Init()
{
	LPC_PINCON->PINSEL4 |= 0x05500000;
	LPC_SC->EXTMODE  |= (0x0F);
  	LPC_SC->EXTPOLAR |= (0x0F);
	NVIC_EnableIRQ(EINT0_IRQn); //---- External interrupt for motor3
	NVIC_EnableIRQ(EINT1_IRQn); //---- External interrupt for motor2
	NVIC_EnableIRQ(EINT2_IRQn); //---- External interrupt for motor1
	NVIC_EnableIRQ(EINT3_IRQn); //---- External interrupt for motor4
	LPC_SC->EXTMODE  |= (0x0F);
  	LPC_SC->EXTPOLAR |= (0x0F);
  	
	//LPC_SC->EXTMODE   = 0x0F ;			   	//all externall interrupts Are edge sensetive 
  	//LPC_SC->EXTPOLAR  = 0x0F ;				//all externall interrupts are rising edge sensetive
}
