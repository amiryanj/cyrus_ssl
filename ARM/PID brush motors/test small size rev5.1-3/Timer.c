#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "timer.h"
#include "defines.h"

#define FOSC                        12000000                            /*  Oscillator frequency                  */

#define FCCLK                      (FOSC  * 8)                          /*  Master clock frequency <= 100Mhz          */
                                                                        /*  Multiples of FOSC                */
#define FCCO                       (FCCLK * 3)                          /*  PLL frequency (275Mhz ~ 550Mhz)      */
                                                                        /*  And FCCLK the same or an even multiple of its */
#define FPCLK                      (FCCLK / 4)                          /*  Peripheral clock frequency, FCCLK 1 / 2, 1 / 4*/
                                                                        /*  The same or FCCLK               */
/*********************************************************************************************************
** Function name:       Timer_Init
** Descriptions:        Initialize timers for Encoders Timing
** input parameters:    No
** output parameters:   No
** Returned value:      No
*********************************************************************************************************/
void Timer_Init (void)
{
    LPC_SC->PCONP |= (1<<1) + (1<<2) + (1<<22) + (1<<23);							//Enables Timer 0,1,2,3
	
	LPC_TIM0->TCR=3;
	LPC_TIM0->TCR=1;
	LPC_TIM1->TCR=3;
	LPC_TIM1->TCR=1;
	LPC_TIM2->TCR=3;
	LPC_TIM2->TCR=1;
	LPC_TIM3->TCR=3;
	LPC_TIM3->TCR=1;
	
	LPC_TIM0->PR = 0x100;
	LPC_TIM1->PR = 0x100;
	LPC_TIM2->PR = 0x100;
	LPC_TIM3->PR = 0x100;
}																

void Timer0Reset(void)
	{
	LPC_TIM0->TCR=3;
	LPC_TIM0->TCR=1;
	}
void Timer1Reset(void)
	{
	LPC_TIM1->TCR=3;
	LPC_TIM1->TCR=1;
	}
void Timer2Reset(void)
	{
	LPC_TIM2->TCR=3;
	LPC_TIM2->TCR=1;
	}
void Timer3Reset(void)
	{
	LPC_TIM3->TCR=3;
	LPC_TIM3->TCR=1;
	}
