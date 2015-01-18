#include <LPC17xx.H>
#include "RIT.h"
 
void RIT_Init(char frequency)
{
	LPC_SC->PCONP |= (1<<16);
	LPC_RIT->RICTRL |= (1<<3) + (1<<1) + 1; // Enable RIT
	//LPC_RIT->RICTRL |= 1<<1; //	Resets on comare match
	LPC_RIT->RICTRL &= ~(1<<2);
	LPC_RIT->RIMASK = 	 0x00000000;
	LPC_RIT->RICOMPVAL = 0xF4240;	  // 40 ms interval
	
	NVIC_EnableIRQ(RIT_IRQn); 		//interrupt for RIT on the speceified time interval 
}