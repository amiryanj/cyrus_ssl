#include "lpc17xx.h"
#include "defines.h"                              /* LPC17xx definitions    */

#define FOSC                        12000000                            /*  Oscillator frequency                  */

#define FCCLK                      (FOSC  * 8)                          /*  Master clock frequency <= 100Mhz          */
                                                                        /*  Multiples of FOSC                */
#define FCCO                       (FCCLK * 3)                          /*  PLL frequency (275Mhz ~ 550Mhz)      */
                                                                        /*  And FCCLK the same or an even multiple of its */
#define FPCLK                      (FCCLK / 4)                          /*  Peripheral clock frequency, FCCLK 1 / 2, 1 / 4*/
                                                                        /*  The same or FCCLK               */

/*********************************************************************************************************
** Function name:       GPIO_Init
** Descriptions:        Initialize Input outputs And pull up resistors
** input parameters:    No
** output parameters:   No
** Returned value:      No
*********************************************************************************************************/
void GPIO_Init()
	{
	 
	 
	 
	 LPC_GPIO4->FIODIR |= (LED_TST1+LED_TST2);
	 LPC_GPIO1->FIODIR |=  LED_TST3;
	
	 LPC_GPIO1->FIODIR &= ~(0x00400000 + 0x20000000);		//Test sswitches for input
	 LPC_GPIO1->FIODIR &= ~(0x00004000 + 0x00008000 + 0x00010000);	//Robot number dipswitch for input

	 LPC_GPIO0->FIODIR &= ~(M1_HALL1 + M1_HALL2 + M1_HALL3);
	 LPC_GPIO0->FIODIR |=  (M1_UL + M1_UH + M1_VL);
	 LPC_GPIO2->FIODIR |=  (M1_VH + M1_WL + M1_WH);
	 LPC_GPIO2->FIODIR |=   M1_ENC_EN;
	 

	 LPC_GPIO0->FIODIR &= ~(M2_HALL1 + M2_HALL2 + M2_HALL3);
	 LPC_GPIO1->FIODIR |=  (M2_UL + M2_UH + M2_VL + M2_VH + M2_WL + M2_WH);

	 LPC_GPIO0->FIODIR &= ~(M3_HALL1 + M3_HALL2 + M3_HALL3);
	 LPC_GPIO1->FIODIR |=  (M3_UL + M3_UH + M3_VL + M3_VH);
	 LPC_GPIO3->FIODIR |=  ( M3_WL + M3_WH);
	 
	 LPC_GPIO0->FIODIR &= ~(M4_HALL1 + M4_HALL2 + M4_HALL3);
	 LPC_GPIO1->FIODIR |=  (M4_UL + M4_UH + M4_VL + M4_VH + M4_WL + M4_WH);


		 
	 
	 
	 //LPC_GPIO1->FIODIR &= ~(ROBO_NUM0 + ROBO_NUM1 + ROBO_NUM2);	// robot number dip as Input
	}
///---End of file

										 