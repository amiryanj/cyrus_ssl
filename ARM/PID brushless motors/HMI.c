#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "defines.h"
#include "hmi.h"

#define FOSC                        12000000                            /*  Oscillator frequency                  */

#define FCCLK                      (FOSC  * 8)                          /*  Master clock frequency <= 100Mhz          */
                                                                        /*  Multiples of FOSC                */
#define FCCO                       (FCCLK * 3)                          /*  PLL frequency (275Mhz ~ 550Mhz)      */
                                                                        /*  And FCCLK the same or an even multiple of its */
#define FPCLK                      (FCCLK / 4)                          /*  Peripheral clock frequency, FCCLK 1 / 2, 1 / 4*/
                                                                        /*  The same or FCCLK               */
/*********************************************************************************************************
** Function name:       Display_number
** Descriptions:        displays a number on the 7 segment
** input parameters:    char number
** output parameters:   No
** Returned value:      No
*********************************************************************************************************/
void Display_number (char number)
{
 char lDigit,uDigit;
 lDigit=(number%10);
 uDigit=(number/10);

 ///--------------------Lower Digit display)----------\\\\
 
 
 LPC_GPIO1->FIOSET |= (L_SEGA + L_SEGB + L_SEGC + L_SEGD + L_SEGE + L_SEGF + L_SEGG + L_SEGDP);
 
 if(lDigit==0)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGD + L_SEGE + L_SEGF); 
	}
 else if(lDigit==1)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGC);
	}
 else if(lDigit==2)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGD + L_SEGE + L_SEGG);
	}
 else if(lDigit==3)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGD + L_SEGG);
	}
 else if(lDigit==4)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGC + L_SEGF + L_SEGG);
	}
 else if(lDigit==5)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGC + L_SEGD + L_SEGF + L_SEGG);
	}
 else if(lDigit==6)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGC + L_SEGD + L_SEGE + L_SEGF + L_SEGG);
	}
 else if(lDigit==7)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC);
	}
 else if(lDigit==8)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGD + L_SEGE + L_SEGF + L_SEGG);
	}
 else if(lDigit==9)
 	{
	LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGD + L_SEGF + L_SEGG);
	}

 ///--------------------Upper Digit display)----------\\\\
 
 LPC_GPIO0->FIOSET |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG); 
 LPC_GPIO1->FIOSET |= (M_SEGB + M_SEGC);
 LPC_GPIO4->FIOSET |= (M_SEGD + M_SEGDP);
 
 if(uDigit==0)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF); 
 	LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 	LPC_GPIO4->FIOCLR |= (M_SEGD );
	}
 else if(uDigit==1)
 	{
	LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
	}
 else if(uDigit==2)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGG); 
 	LPC_GPIO1->FIOCLR |= (M_SEGB);
 	LPC_GPIO4->FIOCLR |= (M_SEGD);
	}
 else if(uDigit==3)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGG); 
 	LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 	LPC_GPIO4->FIOCLR |= (M_SEGD);
	}
 else if(uDigit==4)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGF + M_SEGG); 
 	LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
	}
 else if(uDigit==5)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGF + M_SEGG); 
 	LPC_GPIO1->FIOCLR |= (M_SEGC);
 	LPC_GPIO4->FIOCLR |= (M_SEGD);
	}
 else if(uDigit==6)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG); 
 	LPC_GPIO1->FIOCLR |= (M_SEGC);
 	LPC_GPIO4->FIOCLR |= (M_SEGD);
	}
 else if(uDigit==7)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA); 
 	LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
	}
 else if(uDigit==8)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG); 
 	LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 	LPC_GPIO4->FIOCLR |= (M_SEGD);
	}
 else if(uDigit==9)
 	{
	LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGF + M_SEGG); 
 	LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 	LPC_GPIO4->FIOCLR |= (M_SEGD);
	}
}




void Display_string(unsigned char *s)
	{
	   unsigned char *p,*q;
	   int i=0;;
	   p=s+1;
	   q=s;
	   for(;*p;)
	    {
	   q=p-1;
	   // right Segment
	   LPC_GPIO1->FIOSET |= (L_SEGA + L_SEGB + L_SEGC + L_SEGD + L_SEGE + L_SEGF + L_SEGG + L_SEGDP);
		if( *p== 'a')
			{	// A
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGE + L_SEGF + L_SEGG);
			}	
		else if( *p=='b')
			{	//B
			LPC_GPIO1->FIOCLR |= (L_SEGC + L_SEGD + L_SEGE + L_SEGF + L_SEGG);
			}
		else if( *p=='c')
			{	//c
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGD + L_SEGE + L_SEGF);
			}
		else if( *p=='d')
			{	//d
			LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGC + L_SEGD + L_SEGE + L_SEGG);
			}
		else if( *p=='e')
			{	//e
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGD + L_SEGE + L_SEGF + L_SEGG);
			}
		else if( *p=='f')
			{	//f
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGE + L_SEGF + L_SEGG);
			}
		else if( *p=='g')
			{	//g
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGD + L_SEGF + L_SEGG);
			}
		else if( *p=='h')
			{	//h
			LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGC + L_SEGE + L_SEGF + L_SEGG);
			}
		else if( *p=='i')
			{	//i
			LPC_GPIO1->FIOCLR |= (L_SEGE + L_SEGF);
			}
		else if( *p=='j')
			{	//j
			LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGC + L_SEGD + L_SEGE);
			}
		else if( *p=='k')
			{	//k
			LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGD + L_SEGE + L_SEGF + L_SEGG);
			}
		else if( *p=='l')
			{	//L
			LPC_GPIO1->FIOCLR |= (L_SEGD + L_SEGE + L_SEGF);
			}
		else if( *p=='m')
			{	//m
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGE + L_SEGF);
			}
		else if( *p=='n')
			{	//n
			LPC_GPIO1->FIOCLR |= (L_SEGC + L_SEGE + L_SEGG);
			}
		else if( *p=='o')
			{	//o
			LPC_GPIO1->FIOCLR |= (L_SEGC + L_SEGD + L_SEGE+ L_SEGG);
			}
		else if( *p=='p')
			{	//p
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGE + L_SEGF + L_SEGG);
			}
		else if( *p=='q')
			{	//q
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGB + L_SEGC + L_SEGF + L_SEGG);
			}
		else if( *p=='r')
			{	//r
			LPC_GPIO1->FIOCLR |= (L_SEGE + L_SEGG);
			}
		else if( *p=='s')
			{	//s
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGC + L_SEGD + L_SEGF + L_SEGG);
			}
		else if( *p=='t')
			{	//t
			LPC_GPIO1->FIOCLR |= (L_SEGA + L_SEGE + L_SEGF);
			}
		else if( *p=='u')
			{	//u
			LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGC + L_SEGD + L_SEGE + L_SEGF);
			}
		 else if( *p=='y')
 			{
			LPC_GPIO1->FIOCLR |= (L_SEGB + L_SEGC + L_SEGD + L_SEGF + L_SEGG);
			}
	
	//-----Left segment
	LPC_GPIO0->FIOSET |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG); 
 	LPC_GPIO1->FIOSET |= (M_SEGB + M_SEGC);
 	LPC_GPIO4->FIOSET |= (M_SEGD + M_SEGDP);
	
	if(*q=='a')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
		}
	else if(*q=='b')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='c')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF); 
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='d')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='e')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG); 
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='f')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG);
		}
	else if(*q=='g')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='h')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
		}
	else if(*q=='i')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGF); 
		}
	else if(*q=='j')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='k')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='l')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGF); 
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='m')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
		}
	else if(*q=='n')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGC);
		}
	else if(*q=='o')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='p')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB);
		}
	else if(*q=='q')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
		}
	else if(*q=='r')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGG); 
		}
	else if(*q=='s')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='t')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGA + M_SEGE + M_SEGF); 
		}
	else if(*q=='u')
		{
		LPC_GPIO0->FIOCLR |= (M_SEGE + M_SEGF); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	else if(*q=='y')
 		{
		LPC_GPIO0->FIOCLR |= (M_SEGF + M_SEGG); 
 		LPC_GPIO1->FIOCLR |= (M_SEGB + M_SEGC);
 		LPC_GPIO4->FIOCLR |= (M_SEGD);
		}
	  for(i=0;i<2000000;i++);
	  p++;

	  }
	}

							