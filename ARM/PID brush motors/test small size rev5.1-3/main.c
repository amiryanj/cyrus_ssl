#include "lpc17xx.h"  
#include "uart.h"
#include "pwm.h"
#include "delay.h"
#include "Drive.h"
#include "timer.h"
#include "EXTI.h"
#include "defines.h"
#include "RIT.h"

int RecievePacket[10]=0;
int i=0;

int M1Time=0xFFFF,M1DesireSpeed=0,M1RealSpeed=0,M1PrError=0,M1InError=0,M1DiError=0,M1LastError=0,M1PID,M1FinalSpeed;
int M2Time=0xFFFF,M2DesireSpeed=0,M2RealSpeed=0,M2PrError=0,M2InError=0,M2DiError=0,M2LastError=0,M2PID,M2FinalSpeed;
int M3Time=0xFFFF,M3DesireSpeed=0,M3RealSpeed=0,M3PrError=0,M3InError=0,M3DiError=0,M3LastError=0,M3PID,M3FinalSpeed;
int M4Time=0xFFFF,M4DesireSpeed=0,M4RealSpeed=0,M4PrError=0,M4InError=0,M4DiError=0,M4LastError=0,M4PID,M4FinalSpeed;
float kp=0,ki=0,kd=0;

int Motor1Speed=0,Motor2Speed=0,Motor3Speed=0,Motor4Speed=0;

void RIT_IRQHandler()
{


	LPC_RIT->RICTRL |= 1; //clear interrupt flag


	M1DesireSpeed = RecievePacket[2] ;
	M2DesireSpeed = RecievePacket[3] ;
	M3DesireSpeed = RecievePacket[4] ;
	M4DesireSpeed = RecievePacket[5] ;
//
//	M1FinalSpeed = M1DesireSpeed  ;
//	M2FinalSpeed = M2DesireSpeed  ;
//	M3FinalSpeed = M3DesireSpeed  ;
//	M4FinalSpeed = M4DesireSpeed  ;


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

	M1PID = kp * M1PrError + ki * M1InError + kd * M1DiError ;
	M2PID = kp * M2PrError + ki * M2InError + kd * M2DiError ;
	M3PID = kp * M3PrError + ki * M3InError + kd * M3DiError ;
	M4PID = kp * M4PrError + ki * M4InError + kd * M4DiError ;

	M1FinalSpeed = M1DesireSpeed + M1PID ;
	M2FinalSpeed = M2DesireSpeed + M2PID ;
	M3FinalSpeed = M3DesireSpeed + M3PID ;
	M4FinalSpeed = M4DesireSpeed + M4PID ;
	
	if ( M1DesireSpeed==0 )
		M1FinalSpeed = 0;
	else
		M1FinalSpeed = M1DesireSpeed + M1PID;
	
	if ( M2DesireSpeed==0 )
		M2FinalSpeed = 0;
	else
		M2FinalSpeed = M2DesireSpeed + M2PID;
	
	if ( M3DesireSpeed==0 )
		M3FinalSpeed = 0;
	else
		M3FinalSpeed = M3DesireSpeed + M3PID;
	
	if ( M4DesireSpeed==0 )
		M4FinalSpeed = 0;
	else
		M4FinalSpeed = M4DesireSpeed + M4PID;

   
	if ( !(RecievePacket[1] & 0x80) )
		M1FinalSpeed = (-1)*M1FinalSpeed;
	if ( !(RecievePacket[1] & 0x40) )
		M2FinalSpeed = (-1)*M2FinalSpeed;
	if ( !(RecievePacket[1] & 0x20) )
		M3FinalSpeed = (-1)*M3FinalSpeed;
	if ( !(RecievePacket[1] & 0x10) )
		M4FinalSpeed = (-1)*M4FinalSpeed;




	M1Time=0xFFFF;
	M2Time=0xFFFF;
	M3Time=0xFFFF;
	M4Time=0xFFFF;

	Drive(M1FinalSpeed,M2FinalSpeed,M3FinalSpeed,M4FinalSpeed);

	 
}

void sendpacket (void); 
void UART2_IRQHandler(void);
//char str[]="*A+B+C+D#";
int main()
{
int i;
SystemInit();
PWM_Init();
UART2_Init();
Timer_Init();
EXTI_Init();
RIT_Init(10);
LPC_GPIO2->FIOSET |=M3_ENC_EN;


LPC_GPIO0->FIODIR=0x10208;
LPC_GPIO2->FIODIR=0x20;

Drive(0,0,0,0);

	Timer0Reset();
	Timer1Reset();
	Timer2Reset();
	Timer3Reset();


	while(1)
	{
	sendpacket();
	}

}

void EINT0_IRQHandler()  // motor3 encoder
{
  	LPC_SC->EXTINT |= (0x01); // clear interrupt flag	
	M3Time=LPC_TIM2->TC;
	Timer2Reset();
}

void EINT1_IRQHandler()  // motor2 encoder
{
  	LPC_SC->EXTINT |= (0x02); // clear interrupt flag
	
	M2Time=LPC_TIM1->TC;
	Timer1Reset();
}

void EINT2_IRQHandler()  // motor1 encoder
{
  	LPC_SC->EXTINT |= (0x04); // clear interrupt flag
	M1Time=LPC_TIM0->TC;
	Timer0Reset();

}

void EINT3_IRQHandler()  // motor4 encoder
{
  	LPC_SC->EXTINT |= (0x08); // clear interrupt flag
	
	M4Time=LPC_TIM3->TC;
	Timer3Reset();
}

void call()
{
if( RecievePacket[0]=='*' && RecievePacket[6]=='^' )
{
	if ( !(RecievePacket[1] & 0x40) )
		M1FinalSpeed = (-1)*RecievePacket[2];
	else
		M1FinalSpeed = RecievePacket[2];

	if ( !(RecievePacket[1] & 0x20) )
		M2FinalSpeed = (-1)*RecievePacket[3];
	else
		M2FinalSpeed = RecievePacket[3];

	if ( !(RecievePacket[1] & 0x10) )
		M3FinalSpeed = (-1)*RecievePacket[4];
	else
		M3FinalSpeed = RecievePacket[4];

	if ( !(RecievePacket[1] & 0x8) )
		M4FinalSpeed = (-1)*RecievePacket[5];
	else
		M4FinalSpeed = RecievePacket[5];

}
}

void UART2_IRQHandler(void)
{
   	int data;
	data = UART2_GetChar();
		if ( data == '*' )
		{
			RecievePacket[0]='*';
			i=0;
		}
		if(i>0)
		{
		RecievePacket[i]=data;
		}
		i++;
		if ( i>=9 )
		{
			i=0;
		}
}


void sendpacket()
{
Motor1Speed=10000/M1Time;
Motor2Speed=10000/M2Time;
Motor3Speed=10000/M3Time;
Motor4Speed=10000/M4Time;

UART2_SendByte('*');
//delay(100);
UART2_SendByte(Motor1Speed);
//delay(100);
UART2_SendByte('+');
//delay(100);
UART2_SendByte(Motor2Speed);
//delay(100);
UART2_SendByte('+');
//delay(10);
UART2_SendByte(Motor3Speed);
//delay(100);
UART2_SendByte('+');
delay(100);
UART2_SendByte(Motor4Speed);
//delay(100);
UART2_SendByte('#');
//delay(100);

}


