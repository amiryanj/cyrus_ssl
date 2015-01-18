#ifndef __DEFINES_H 

#define __DEFINES_H
#define MAX_DUTY 255  		// Maximum duty cycle for PWMs

#define LED_TST1 0x10000000 	//Port4.28
#define LED_TST2 0x20000000		//Port4.29
#define LED_TST3 0x00020000 	//Port1.17

//#define TST_SW1	 0x00400000		//Port1.22
//#define TST_SW2	 0x20000000		//Port1.29

#define TST_SW1 ((LPC_GPIO1->FIOPIN >> 29)&1)==0
#define TST_SW2 ((LPC_GPIO1->FIOPIN >> 22)&1)==0

//--------------------Motor 1 Configuration
#define M1_SPEED LPC_PWM1->MR2
#define M1_HALL1 0x00000100		//Port0.8
#define M1_HALL2 0x00000080		//Port0.7
#define M1_HALL3 0x00080000		//Port0.19

#define M1_UL	0x00000020 		//Port0.5
#define M1_UH	0x00000010 		//Port0.4
#define M1_VL	0x00000200 		//Port0.9
#define M1_VH	0x00000040 		//Port2.6
#define M1_WL	0x00000100 		//Port2.8
#define M1_WH	0x00000080 		//Port2.7

#define M1SET LPC_GPIO0->FIOSET 
#define M1CLR LPC_GPIO0->FIOCLR
#define M1SETW LPC_GPIO2->FIOSET 
#define M1CLRW LPC_GPIO2->FIOCLR

#define M1_ENC_EN (0x200)	//PORT2.9

//--------------------Motor 2 Configuration
#define M2_SPEED LPC_PWM1->MR3
#define M2_HALL1 0x00400000		//Port0.22
#define M2_HALL2 0x00200000		//Port0.21
#define M2_HALL3 0x00100000		//Port0.20

#define M2_UL	0x10000000 		//Port1.28
#define M2_UH	0x08000000 		//Port1.27
#define M2_VL	0x02000000 		//Port1.25
#define M2_VH	0x04000000 		//Port1.26
#define M2_WL	0x01000000 		//Port1.24
#define M2_WH	0x00800000 		//Port1.23

#define M2SET LPC_GPIO1->FIOSET 
#define M2CLR LPC_GPIO1->FIOCLR

//--------------------Motor 3 Configuration
#define M3_SPEED LPC_PWM1->MR6
#define M3_HALL1 0x08000000		//Port0.27
#define M3_HALL2 0x10000000		//Port0.28
#define M3_HALL3 0x00800000		//Port0.23

#define M3_UL	0x00200000 		//Port1.21
#define M3_UH	0x00100000 		//Port1.20
#define M3_VL	0x00040000 		//Port1.18
#define M3_VH	0x00080000 		//Port1.19
#define M3_WL	0x02000000 		//Port3.25
#define M3_WH	0x04000000 		//Port3.26

#define M3SET LPC_GPIO1->FIOSET 
#define M3CLR LPC_GPIO1->FIOCLR
#define M3SETW LPC_GPIO3->FIOSET 
#define M3CLRW LPC_GPIO3->FIOCLR


//--------------------Motor 4 Configuration
#define M4_SPEED LPC_PWM1->MR1
#define M4_HALL1 0x04000000		//Port0.26
#define M4_HALL2 0x01000000		//Port0.24
#define M4_HALL3 0x02000000		//Port0.25

#define M4_UL	0x00000002 		//Port1.1
#define M4_UH	0x00000001 		//Port1.0
#define M4_VL	0x00000010 		//Port1.4
#define M4_VH	0x00000100 		//Port1.8
#define M4_WL	0x00000400 		//Port1.10
#define M4_WH	0x00000200 		//Port1.9

#define M4SET LPC_GPIO1->FIOSET 
#define M4CLR LPC_GPIO1->FIOCLR 

#define M1_DIR (0x20) 		// Port2.5
#define M2_DIR (0x8)  		//PORT0.3
#define M3_DIR (0x200)		// PORT0.9
#define M4_DIR (0x10000) 	//PORT0.16


#define TEST_BUTT (0x80000000)	//PORT1.31
#define MODE_SW (0x10) 		//PORT2.4 

#define ROBO_NUM0 (0x40000) //PORT1.18
#define ROBO_NUM1 (0x80000)	//PORT1.19
#define ROBO_NUM2 (0x100000)	//PORT1.20
#define TRUE 1
#define FALSE 0



///-----Controller values-----\\\


#define KP_POS 0.5f	  // Coefficient for positive errors
#define KP_NEG 1.3f	  // Coefficient for negative errors
#define KI 0.7f
#define KD 0.5f
#define LOWSPEEDPR 1.4f

#endif
