#ifndef __DEFINES_H 

#define __DEFINES_H
#define MAX_DUTY 255  		// Maximum duty cycle for PWMs

#define M1_DIR (0x20) 		// Port2.5
#define M2_DIR (0x8)  		//PORT0.3
#define M3_DIR (0x200)		// PORT0.9
#define M4_DIR (0x10000) 	//PORT0.16

#define L_SEGA (0x8000)		//PORT1.15 
#define L_SEGB (0x10)		//PORT1.4
#define L_SEGC (0x2)		//PORT1.1
#define L_SEGD (0x100)		//PORT1.8
#define L_SEGE (0x200)		//PORT1.9
#define L_SEGF (0x4000)		//PORT1.14
#define L_SEGG (0x400)		//PORT1.10
#define L_SEGDP (0x1)		//PORT1.0

#define M_SEGA 	(0x20)		//PORT0.5
#define M_SEGB	(0x10000)	//PORT1.16
#define M_SEGC	(0x20000)	//PORT1.17
#define M_SEGD	(0x10000000)	//PORT4.28
#define M_SEGE	(0x10)		//PORT0.4
#define M_SEGF	(0x80)		//PORT0.7
#define M_SEGG	(0x100)		//PORT0.8
#define M_SEGDP	(0x20000000)	//PORT4.29

#define M3_ENC_EN (0x200)	//PORT2.9

#define TEST_BUTT (0x80000000)	//PORT1.31
#define MODE_SW (0x10) 		//PORT2.4 

#define ROBO_NUM0 (0x40000) //PORT1.18
#define ROBO_NUM1 (0x80000)	//PORT1.19
#define ROBO_NUM2 (0x100000)	//PORT1.20
#define TRUE 1
#define FALSE 0



///-----Controller values-----\\\


#define KP 1.4f
#define KI 0.9f
#define KD 0.8f

#endif
