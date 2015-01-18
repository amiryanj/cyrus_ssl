#include <LPC17xx.H>
#include "pwm.h"
#include "uart.h"
#include "GPIO.h"
#include "EXTI.h"
#include "RIT.h"
#include "Timer.h"
#include "defines.h"



//----Function Headers
void updateTasks(void);
void UART0_IRQHandler(void);
void LEDblue(char brightness);
void LEDwhite(char brightness);
void switchDelay(void);
void sendpacket(void);

//------Global Variables
signed char comDataCounter=-1;
char validDataFlag=0;
char RecievePacket[10]={0};
char robotNumber=0;
int i=0;
float kp=0,ki=0,kd=0;


int  noDataTime=0;
char M1Dir=0,M1RealDir=0;
char M2Dir=0,M2RealDir=0;
char M3Dir=1,M3RealDir=0;
char M4Dir=1,M4RealDir=0;

int counter1=0,counter2=0;

int M1Time=0xFFFF,M1DesireSpeed=0,M1RealSpeed=0,M1PrError=0,M1InError=0,M1DiError=0,M1LastError=0,M1PID=0,M1FinalSpeed=0;
int M2Time=0xFFFF,M2DesireSpeed=0,M2RealSpeed=0,M2PrError=0,M2InError=0,M2DiError=0,M2LastError=0,M2PID=0,M2FinalSpeed=0;
int M3Time=0xFFFF,M3DesireSpeed=0,M3RealSpeed=0,M3PrError=0,M3InError=0,M3DiError=0,M3LastError=0,M3PID=0,M3FinalSpeed=0;
int M4Time=0xFFFF,M4DesireSpeed=0,M4RealSpeed=0,M4PrError=0,M4InError=0,M4DiError=0,M4LastError=0,M4PID=0,M4FinalSpeed=0; 

char M1HallState=10,M1TimeReverse=0,M1LastHallState=10;
char M2HallState=10,M2TimeReverse=0,M2LastHallstate=10;
char M3HallState=10,M3TimeReverse=0,M3LastHallState=10;
char M4HallState=10,M4TimeReverse=0,M4LastHallState=10;


void PWM_Initialize(void)
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

	/* All single edge, all enable */
	LPC_PWM1->PCR = PWMENA1 | PWMENA2 | PWMENA3 | PWMENA4 | PWMENA5 | PWMENA6;
	LPC_PWM1->TCR = TCR_CNT_EN | TCR_PWM_EN;	/* counter enable, PWM enable */


}




void RIT_IRQHandler()
{
	LPC_RIT->RICTRL |= 1; //clear interrupt flag



	M1DesireSpeed = RecievePacket[2] ;
	M2DesireSpeed = RecievePacket[3] ;
	M3DesireSpeed = RecievePacket[4] ;
	M4DesireSpeed = RecievePacket[5] ;


	kp = RecievePacket[6]/100.0;
	ki = RecievePacket[7]/100.0;
	kd = RecievePacket[8]/100.0; 
	
//	kp=0.5;
//	ki=0.1;
//	kd=0.05;


	M1RealSpeed = 10000/M1Time ;
	M2RealSpeed = 10000/M2Time ;
	M3RealSpeed = 10000/M3Time ;
	M4RealSpeed = 10000/M4Time ;
		
	
	M1PrError = M1DesireSpeed - M1RealSpeed ;
	M2PrError = M2DesireSpeed - M2RealSpeed ;
	M3PrError = M3DesireSpeed - M3RealSpeed ;
	M4PrError = M4DesireSpeed - M4RealSpeed ;

	M1InError += M1PrError ;
	M2InError += M2PrError ;
	M3InError += M3PrError ;
	M4InError += M4PrError ;

	M1DiError = M1PrError - M1LastError ;
	M2DiError = M2PrError - M2LastError ;
	M3DiError = M3PrError - M3LastError ;
	M4DiError = M4PrError - M4LastError ;

	M1LastError = M1PrError ;
	M2LastError = M2PrError ;
	M3LastError = M3PrError ;
	M4LastError = M4PrError ;

	if (M1DesireSpeed == 0)
		{
			M1PrError=0;
			M1InError=0;
			M1DiError=0;
		}
	if (M2DesireSpeed == 0)
		{
			M2PrError=0;
			M2InError=0;
			M2DiError=0;
		}
	if (M3DesireSpeed == 0)
		{
			M3PrError=0;
			M3InError=0;
			M3DiError=0;
		}
	if (M4DesireSpeed == 0)
		{
			M4PrError=0;
			M4InError=0;
			M4DiError=0;
		}


	M1PID = kp * M1PrError + ki * M1InError + kd * M1DiError ;
	M2PID = kp * M2PrError + ki * M2InError + kd * M2DiError ;
	M3PID = kp * M3PrError + ki * M3InError + kd * M3DiError ;
	M4PID = kp * M4PrError + ki * M4InError + kd * M4DiError ;

	if ( !(RecievePacket[1] & 0x80) )
		M1Dir=1;
	else
		M1Dir=0;
	if ( !(RecievePacket[1] & 0x40) )
		M2Dir=1;
	else
		M2Dir=0;
	if ( !(RecievePacket[1] & 0x20) )
		M3Dir=1;
	else
		M3Dir=0;
	if ( !(RecievePacket[1] & 0x10) )
		M4Dir=1;
	else
		M4Dir=0;

	M1FinalSpeed = M1DesireSpeed + M1PID; 
	M2FinalSpeed = M2DesireSpeed + M2PID;
	M3FinalSpeed = M3DesireSpeed + M3PID;
	M4FinalSpeed = M4DesireSpeed + M4PID;

	LEDblue(0);
}

int Q=0;


int main()
{
SystemInit();
UART0_Init();
PWM_Init();
GPIO_Init();
//Timers Init
Timer_Init();
//	RIT Initialize for controller loop 
RIT_Init(10);
//External interrupts initialize for encoders
EXTI_Init();

LPC_GPIO2->FIOSET |=M1_ENC_EN; // Enables the encoder of Motor1

 	Timer0Reset();
	Timer1Reset();
	Timer2Reset();
	Timer3Reset();

    M1Time=0xFFFF;
	M2Time=0xFFFF;
	M3Time=0xFFFF;
	M4Time=0xFFFF;
while(1)
	{
//	LEDwhite(0);
	LEDblue (0);
//
//M1RealSpeed=19000/M1Time;
//M2RealSpeed=19000/M2Time;
//M3RealSpeed=19000/M3Time;
//M4RealSpeed=19000/M4Time;

//	if ( Q==0 )
//		UART0_SendByte('*');
//	else if ( Q==1 )
//		UART0_SendByte(19000/M1Time);
//	else if ( Q==2 )
//		UART0_SendByte('+');
//	else if ( Q==3 )
//		UART0_SendByte(19000/M2Time);
//	else if ( Q==4 )
//		UART0_SendByte('+');
//	else if ( Q==5 )
//		UART0_SendByte(19000/M3Time);
//	else if ( Q==6 )
//		UART0_SendByte('+');
//	else if ( Q==7 )
//		UART0_SendByte(19000/M4Time);
//	else if ( Q==8 )
//	{
//		UART0_SendByte('#');
//		LEDblue(200);
//		Q=-1;
//	}
//	
//	Q++;


//
//	if (Q>=25000)
//	{
//		Q=0;
//		LEDblue(255);
//		sendpacket();
//		LEDblue(0);
//	}
	M1_SPEED = M1FinalSpeed;

	M2_SPEED = M2FinalSpeed;

	M3_SPEED = M3FinalSpeed;

	M4_SPEED = M4FinalSpeed;


	LPC_PWM1->LER |= LER2_EN;
	LPC_PWM1->LER |= LER3_EN;
	LPC_PWM1->LER |= LER6_EN;
	LPC_PWM1->LER |= LER1_EN;
	
	M1HallState=((LPC_GPIO0->FIOPIN>>8)&1) + ((LPC_GPIO0->FIOPIN>>6)&2) + ((LPC_GPIO0->FIOPIN>>17)&4);	
	M2HallState=((LPC_GPIO0->FIOPIN>>22)&1) + ((LPC_GPIO0->FIOPIN>>20)&2) + ((LPC_GPIO0->FIOPIN>>18)&4);	
	M3HallState=((LPC_GPIO0->FIOPIN>>27)&1) + ((LPC_GPIO0->FIOPIN>>27)&2) + ((LPC_GPIO0->FIOPIN>>21)&4);	
	M4HallState=((LPC_GPIO0->FIOPIN>>26)&1) + ((LPC_GPIO0->FIOPIN>>23)&2) + ((LPC_GPIO0->FIOPIN>>23)&4);			
	if(M1Dir==0)   ///--------------Clockwise rotation
	{
		if(M1HallState==3)
			{
			M1CLR = M1_UL;
			M1CLR = M1_UH;
			M1CLRW = M1_WH;
			M1CLR = M1_VL;
			
			switchDelay();
			M1SETW = M1_VH;
			M1SETW = M1_WL;
			
			}
		else if(M1HallState==1)
			{
			M1CLR = M1_UL;
			M1CLRW = M1_WH;
			M1CLR = M1_VL;
			M1CLRW = M1_VH;
			
			switchDelay();
			M1SET = M1_UH;
			M1SETW = M1_WL;
			
			}
		else if(M1HallState==5)
			{
			M1CLR = M1_UL;
			M1CLRW = M1_VH;
			M1CLRW = M1_WL;
			M1CLRW = M1_WH;

			switchDelay();
			M1SET = M1_UH;
			M1SET = M1_VL;
			}
		else if(M1HallState==4)
			{
			M1CLR = M1_UL;
			M1CLR = M1_UH;
			M1CLRW = M1_VH;
			M1CLRW = M1_WL;
			
			switchDelay();
			M1SET = M1_VL;
			M1SETW = M1_WH;
			}
		else if(M1HallState==6)
			{
			M1CLR = M1_UH;
			M1CLR = M1_VL;
			M1CLRW = M1_VH;
			M1CLRW = M1_WL;
			
			switchDelay();
			M1SET = M1_UL;
			M1SETW = M1_WH;
			}
		else if(M1HallState==2)
			{
			M1CLR = M1_UH;
			M1CLR = M1_VL;
			M1CLRW = M1_WL;
			M1CLRW = M1_WH;
			
			switchDelay();
			M1SET = M1_UL;
			M1SETW = M1_VH;
			}
		}
		
	else if(M1Dir==1)		//CClockwise roattion
		{
		if(M1HallState==4)
			{
			M1CLR = M1_UL;
			M1CLR = M1_UH;
			M1CLR = M1_VL;
			M1CLRW = M1_WH;
			
			switchDelay();
			M1SETW = M1_VH;
			M1SETW = M1_WL;
			}
		else if(M1HallState==6)
			{
			M1CLR = M1_UL;
			M1CLRW = M1_WH;			
			M1CLR = M1_VL;
			M1CLRW = M1_VH;
			
			switchDelay();
			M1SETW = M1_WL;
			M1SET = M1_UH;
			}
		else if(M1HallState==2)
			{
			M1CLR = M1_UL;
			M1CLRW = M1_VH;
			M1CLRW = M1_WL;
			M1CLRW = M1_WH;
			
			switchDelay();
			M1SET = M1_UH;
			M1SET = M1_VL;
			}
		else if(M1HallState==3)
			{
			M1CLR = M1_UL;
			M1CLR = M1_UH;
			M1CLRW = M1_VH;
			M1CLRW = M1_WL;
			
			switchDelay();
			M1SET = M1_VL;
			M1SETW = M1_WH;
			}
		else if(M1HallState==1)
			{
			M1CLR = M1_UH;
			M1CLR = M1_VL;
			M1CLRW = M1_VH;
			M1CLRW = M1_WL;
			
			switchDelay();
			M1SET = M1_UL;
			M1SETW = M1_WH;
			}
		else if(M1HallState==5)
			{
			M1CLR = M1_UH;
			M1CLR = M1_VL;
			M1CLRW = M1_WL;
			M1CLRW = M1_WH;
			
			switchDelay();
			M1SET = M1_UL;
			M1SETW = M1_VH;
			}
		}

			if(M2Dir==0)
	{
		if(M2HallState==3)
			{
			M2CLR = M2_UL;
			M2CLR = M2_UH;
			M3CLR = M2_VL;
			M2CLR = M2_WH;
			
			switchDelay();
			M3SET = M2_VH;
			M2SET = M2_WL;
			}
		else if(M2HallState==1)
			{
			M2CLR = M2_UL;
			M2CLR = M2_VL;
			M2CLR = M2_VH;
			M2CLR = M2_WH;
			
			switchDelay();
			M2SET = M2_WL;
			M2SET = M2_UH;
			}
		else if(M2HallState==5)
			{
			M2CLR = M2_UL;
			M2CLR = M2_VH;
			M2CLR = M2_WL;
			M2CLR = M2_WH;
			
			switchDelay();
			M2SET = M2_UH;
			M2SET = M2_VL;
			}
		else if(M2HallState==4)
			{
			M2CLR = M2_UL;
			M2CLR = M2_UH;
			M2CLR = M2_VH;
			M2CLR = M2_WL;
			
			switchDelay();
			M2SET = M2_VL;
			M2SET = M2_WH;
			}
		else if(M2HallState==6)
			{
			
			M2CLR = M2_UH;
			M2CLR = M2_VL;
			M2CLR = M2_VH;
			M2CLR = M2_WL;
			
			switchDelay();
			M2SET = M2_UL;
			M2SET = M2_WH;
			}
		else if(M2HallState==2)
			{
			
			M2CLR = M2_UH;
			M2CLR = M2_VL;
			M2CLR = M2_WL;
			M2CLR = M2_WH;
			
			switchDelay();
			M2SET = M2_UL;
			M2SET = M2_VH;
			}
		}
	else
		{
		if(M2HallState==4)
			{
			M2CLR = M2_UL;
			M2CLR = M2_UH;
			M3CLR = M2_VL;
			M2CLR = M2_WH;
			
			switchDelay();
			M3SET = M2_VH;
			M2SET = M2_WL;
			}
		else if(M2HallState==6)
			{
			M2CLR = M2_UL;
			M2CLR = M2_VL;
			M2CLR = M2_VH;
			M2CLR = M2_WH;
			
			switchDelay();
			M2SET = M2_UH;
			M2SET = M2_WL;
			}
		else if(M2HallState==2)
			{
			M2CLR = M2_UL;
			M2CLR = M2_VH;
			M2CLR = M2_WL;
			M2CLR = M2_WH;
			
			switchDelay();
			M2SET = M2_UH;
			M2SET = M2_VL;
			}
		else if(M2HallState==3)
			{
			M2CLR = M2_UL;
			M2CLR = M2_UH;
			M2CLR = M2_VH;
			M2CLR = M2_WL;
			
			switchDelay();
			M2SET = M2_VL;
			M2SET = M2_WH;
			}
		else if(M2HallState==1)
			{
			M2CLR = M2_UH;
			M2CLR = M2_VL;
			M2CLR = M2_VH;
			M2CLR = M2_WL;
			
			switchDelay();
			M2SET = M2_UL;
			M2SET = M2_WH;
			}
		else if(M2HallState==5)
			{
			M2CLR = M2_UH;
			M2CLR = M2_VL;
			M2CLR = M2_WL;
			M2CLR = M2_WH;
			
			switchDelay();
			M2SET = M2_VH;
			M2SET = M2_UL;
			}
		
		}

	if(M3Dir==0)
	{
		if(M3HallState==3)
			{
			M3CLR = M3_UL;
			M3CLR = M3_UH;
			M3CLR = M3_VL;
			M3CLRW = M3_WH;
			
			switchDelay();
			M3SET = M3_VH;
			M3SETW = M3_WL;
			}
		else if(M3HallState==1)
			{
			M3CLR = M3_UL;
			M3CLR = M3_VL;
			M3CLR = M3_VH;
			M3CLRW = M3_WH;
			
			switchDelay();
			M3SET = M3_UH;
			M3SETW = M3_WL;
			}
		else if(M3HallState==5)
			{
			M3CLR = M3_UL;
			M3CLR = M3_VH;
			M3CLRW = M3_WL;
			M3CLRW = M3_WH;
			
			switchDelay();
			M3SET = M3_UH;
			M3SET = M3_VL;
			}
		else if(M3HallState==4)
			{
			M3CLR = M3_UL;
			M3CLR = M3_UH;
			M3CLR = M3_VH;
			M3CLRW = M3_WL;
			
			switchDelay();
			M3SETW = M3_WH;
			M3SET = M3_VL;
			}
		else if(M3HallState==6)
			{
			
			M3CLR = M3_UH;
			M3CLR = M3_VL;
			M3CLR = M3_VH;
			M3CLRW = M3_WL;
			
			switchDelay();
			M3SET = M3_UL;
			M3SETW = M3_WH;
			}
		else if(M3HallState==2)
			{
			
			M3CLR = M3_UH;
			M3CLR = M3_VL;
			M3CLRW = M3_WL;
			M3CLRW = M3_WH;
			
			switchDelay();
			M3SET = M3_UL;
			M3SET = M3_VH;
			}
		}
	else
		{
		
		if(M3HallState==4)
			{
			M3CLR = M3_UL;
			M3CLR = M3_UH;
			M3CLR = M3_VL;
			M3CLRW = M3_WH;
			
			switchDelay();
			M3SET = M3_VH;
			M3SETW = M3_WL;
			}
		else if(M3HallState==6)
			{
			M3CLR = M3_UL;
			M3CLR = M3_VL;
			M3CLR = M3_VH;
			M3CLRW = M3_WH;
			
			switchDelay();
			M3SETW = M3_WL;
			M3SET = M3_UH;
			}
		else if(M3HallState==2)
			{
			M3CLR = M3_UL;
			M3CLR = M3_VH;
			M3CLRW = M3_WL;
			M3CLRW = M3_WH;
			
			switchDelay();
			M3SET = M3_UH;
			M3SET = M3_VL;
			}
		else if(M3HallState==3)
			{
			M3CLR = M3_UL;
			M3CLR = M3_UH;
			M3CLR = M3_VH;
			M3CLRW = M3_WL;
			
			switchDelay();
			M3SETW = M3_WH;
			M3SET = M3_VL;
			}
		else if(M3HallState==1)
			{
			M3CLR = M3_UH;
			M3CLR = M3_VL;
			M3CLR = M3_VH;
			M3CLRW = M3_WL;
			
			switchDelay();
			M3SETW = M3_WH;
			M3SET = M3_UL;
			}
		else if(M3HallState==5)
			{
			M3CLR = M3_UH;
			M3CLRW = M3_WL;
			M3CLRW = M3_WH;
			M3CLR = M3_VL;
			
			switchDelay();
			M3SET = M3_VH;
			M3SET = M3_UL;
			}
		}

		
		
	if(M4Dir==0)
		{	
		if(M4HallState==3)
			{
			M4CLR = M4_UL;
			M4CLR = M4_UH;
			M4CLR = M4_WH;
			M4CLR = M4_VL;
			
			switchDelay();
			M4SET = M4_VH;
			M4SET = M4_WL;
			}
		else if(M4HallState==1)
			{
			M4CLR = M4_UL;
			M4CLR = M4_WH;
			M4CLR = M4_VL;
			M4CLR = M4_VH;
			
			switchDelay();
			M4SET = M4_UH;
			M4SET = M4_WL;
			}
		else if(M4HallState==5)
			{
			M4CLR = M4_UL;
			M4CLR = M4_VH;
			M4CLR = M4_WL;
			M4CLR = M4_WH;
			
			switchDelay();
			M4SET = M4_UH;
			M4SET = M4_VL;
			}
		else if(M4HallState==4)
			{
			M4CLR = M4_UL;
			M4CLR = M4_UH;
			M4CLR = M4_VH;
			M4CLR = M4_WL;
			
			switchDelay();
			M4SET = M4_WH;
			M4SET = M4_VL;
			}
		else if(M4HallState==6)
			{
			M4CLR = M4_UH;
			M4CLR = M4_VL;
			M4CLR = M4_VH;
			M4CLR = M4_WL;
			
			switchDelay();
			M4SET = M4_WH;
			M4SET = M4_UL;
			}
		else if(M4HallState==2)
			{
			M4CLR = M4_UH;
			M4CLR = M4_VL;
			M4CLR = M4_WL;
			M4CLR = M4_WH;
			
			switchDelay();
			M4SET = M4_UL;
			M4SET = M4_VH;
			}
		 }
	else
		{
		
		if(M4HallState==4)
			{
			M4CLR = M4_UL;
			M4CLR = M4_UH;
			M4CLR = M4_VL;
			M4CLR = M4_WH;
			
			switchDelay();
			M4SET = M4_WL;
			M4SET = M4_VH;
			}
		else if(M4HallState==6)
			{
			M4CLR = M4_UL;
			M4CLR = M4_VL;
			M4CLR = M4_VH;
			M4CLR = M4_WH;
			
			switchDelay();
			M4SET = M4_WL;
			M4SET = M4_UH;
			}
		else if(M4HallState==2)
			{
			M4CLR = M4_UL;
			M4CLR = M4_VH;
			M4CLR = M4_WL;
			M4CLR = M4_WH;
			
			switchDelay();
			M4SET = M4_UH;
			M4SET = M4_VL;
			}
		else if(M4HallState==3)
			{
			M4CLR = M4_UL;
			M4CLR = M4_UH;
			M4CLR = M4_VH;
			M4CLR = M4_WL;
			
			switchDelay();
			M4SET = M4_WH;
			M4SET = M4_VL;
			}
		else if(M4HallState==1)
			{
			
			M4CLR = M4_UH;
			M4CLR = M4_VL;
			M4CLR = M4_VH;
			M4CLR = M4_WL;
			
			switchDelay();
			M4SET = M4_WH;
			M4SET = M4_UL;
			}
		else if(M4HallState==5)
			{
			
			M4CLR = M4_UH;
			M4CLR = M4_VL;
			M4CLR = M4_WL;
			M4CLR = M4_WH;
			
			switchDelay();
			M4SET = M4_UL;
			M4SET = M4_VH;
			}
		}
		
		////		Motor 1 on leds

		if(((LPC_GPIO0->FIOPIN>>8)&1) == 0)
			{
			LPC_GPIO4->FIOCLR|=LED_TST1;
			}
			else
			{
			LPC_GPIO4->FIOSET|=LED_TST1;
			}

		if(((LPC_GPIO0->FIOPIN>>7)&1) == 0)
			{
			LPC_GPIO4->FIOCLR|=LED_TST2;
			}
			else
			{
			LPC_GPIO4->FIOSET|=LED_TST2;
			}

		if(((LPC_GPIO0->FIOPIN>>19)&1) == 0)
			{
			LPC_GPIO1->FIOCLR|=LED_TST3;
			}
			else
			{
			LPC_GPIO1->FIOSET=LED_TST3;
			}
	}
}

void LEDblue(char brightness)
{
	LPC_PWM1->MR5 = brightness ;
	LPC_PWM1->LER |=LER5_EN;	
}

void LEDwhite(char brightness)
{
	LPC_PWM1->MR4 = brightness ;
	LPC_PWM1->LER |= LER4_EN;	
}

void switchDelay()
{
	char i;
	for(i=0;i<10;i++);
}


//------Externall interrupts to messure motors Speed
void EINT0_IRQHandler()  // motor1 encoder
{
  	LPC_SC->EXTINT |= (0x01); // clear interrupt flag	
	M1Time=LPC_TIM2->TC;
	Timer2Reset();
}

void EINT1_IRQHandler()  // motor2 encoder
{
  	LPC_SC->EXTINT |= (0x02); // clear interrupt flag
	M2Time=LPC_TIM1->TC;
	Timer1Reset();
}

void EINT2_IRQHandler()  // motor4 encoder
{
  	LPC_SC->EXTINT |= (0x04); // clear interrupt flag
	M4Time=LPC_TIM0->TC;
	Timer0Reset();

}

void EINT3_IRQHandler()  // motor3 encoder
{
  	LPC_SC->EXTINT |= (0x08); // clear interrupt flag
	M3Time=LPC_TIM3->TC;
	Timer3Reset();
}


void sendpacket()
{
M1RealSpeed=19000/M1Time;
M2RealSpeed=19000/M2Time;
M3RealSpeed=19000/M3Time;
M4RealSpeed=19000/M4Time;
//fuck='*'+M1RealSpeed+'+'+M2RealSpeed+'+'+M3RealSpeed+'+'+M4RealSpeed+'#';
//
//UART0_SendByte(fuck);

UART0_SendByte('*');
//delay(100);
UART0_SendByte(M1RealSpeed);
//delay(100);
UART0_SendByte('+');
//delay(100);
UART0_SendByte(M2RealSpeed);
//delay(100);
UART0_SendByte('+');
//delay(10);
UART0_SendByte(M3RealSpeed);
//delay(100);
UART0_SendByte('+');
//delay(100);
UART0_SendByte(M4RealSpeed);
//delay(100);
UART0_SendByte('#');
//delay(100);

}

//----Updating the tasks, received from Server
//void updateTasks()
//{
//	char direct=0;
//	noDataTime=0;
//		
//	M1DesireSpeed=comPacket[1];
//	M2DesireSpeed=comPacket[2];
//	M3DesireSpeed=comPacket[3];
//	M4DesireSpeed=comPacket[4];
//	
//
//	M1Dir = ((comPacket[0] & 0x10)>>4);
//	M2Dir = ((comPacket[0] & 0x20)>>5);
//	M3Dir = ((comPacket[0] & 0x40)>>6);
//	M4Dir = ((comPacket[0] & 0x80)>>7);
//
//  /*
//	if( (comPacket[5] & 0x0F) == ((comPacket[5] & 0xF0)>>4) )
//		{
//		if(Kick_sens()>125)
//			{
//			UART3_SendByte((comPacket[5] & 0x0F) + 47);
//			}
//		}
//		*/
//				   		
//}


////UART0 Interrupt Handler ---->>Computer Communication 

void UART0_IRQHandler(void)
{
	
	int data;
	data = UART0_GetChar();
	LEDwhite(0);
		if ( data == '&' )
		{
			RecievePacket[0]='&';
			i=0;
			LEDwhite(200);
		}
		if(i>0)
		{
			RecievePacket[i]=data;
			//LEDwhite(200);
		}
		i++;
		if ( i>=9 )
		{
			i=0;
			LEDwhite(200);
		}

	
	
	
	/*
	
	if ( data == 'w')
		{
		   M1DesireSpeed=200;
		   M2DesireSpeed=200;
		   M3DesireSpeed=200;
		   M4DesireSpeed=200;

		   M1Dir=0;
		   M2Dir=0;
		   M3Dir=1;
		   M4Dir=1;
		}
	else if ( data == 's')
		{
		   M1DesireSpeed=200;
		   M2DesireSpeed=200;
		   M3DesireSpeed=200;
		   M4DesireSpeed=200;

		   M1Dir=1;
		   M2Dir=1;
		   M3Dir=0;
		   M4Dir=0;
		}
	else if ( data == 'a')
		{
		   M1DesireSpeed=130;
		   M2DesireSpeed=130;
		   M3DesireSpeed=130;
		   M4DesireSpeed=130;

		   M1Dir=0;
		   M2Dir=1;
		   M3Dir=1;
		   M4Dir=0;
		}
		else if ( data == 'd')
		{
		   M1DesireSpeed=130;
		   M2DesireSpeed=130;
		   M3DesireSpeed=130;
		   M4DesireSpeed=130;

		   M1Dir=1;
		   M2Dir=0;
		   M3Dir=0;
		   M4Dir=1;
		}
		else if ( data == 'r')
		{
		   M1DesireSpeed=30;
		   M2DesireSpeed=30;
		   M3DesireSpeed=30;
		   M4DesireSpeed=30;

		   M1Dir=0;
		   M2Dir=0;
		   M3Dir=0;
		   M4Dir=0;
		}
		else if ( data == ' ')
		{
		   M1DesireSpeed=0;
		   M2DesireSpeed=0;
		   M3DesireSpeed=0;
		   M4DesireSpeed=0;

		   M1Dir=0;
		   M2Dir=0;
		   M3Dir=1;
		   M4Dir=1;
		}
	  	*/


}
