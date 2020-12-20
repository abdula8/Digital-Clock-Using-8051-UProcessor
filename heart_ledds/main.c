#include <reg52.h>
#include "Ports.h"
#include "Interrupt.h"
#include "Delay.h"
#include "DataTypes.h"
// # Owner Abdullah Atef
#define TIMER_COUNTER 5

boolean isLeftDir=true;
boolean isOk=true;
tWord ticks=0;
typedef enum {LeftDir, RightDir} states;
states curState=LeftDir;


void initialization();
void operation();
void GOTO_SLEEP();

void main(void){
	initialization();
	operation();
}
void GOTO_SLEEP(){
	PCON |=1; // power down mode
}
void initialization(){
	//ButtonPort=0xff;
	led_9=0;
	LedsPort=0;
	Delay_ms(1);
	LedsPort=1;
	Ex0Pin = 1;
	Ex1Pin = 1;
	/*TMOD=1;
	TH0=0x3C;
	TL0=0xB0;
	TR0=1;*/
	
	// TIMER 2
	T2CON = 0x04; 		// Load Timer 2 Control Register
	TH2 = 0x3C;  			// Load Timer 2 high byte
	RCAP2H = 0x3C; 		// Load Timer 2 reload Capt. reg. high byte
	TL2 = 0xB0;  			// Load Timer 2 Low byte
	RCAP2L = 0xB0; 		// Load Timer 2 reload Capt. reg. low byte
	TR2 = 1;	 				// Start Timer 2
	IT0 = 1; 					// EX0 INT0 Edge Triggred
	IE=0xA5; 					// 1010 0000 TO Enabel Timer 2 Interrupt INT0 and INT1

}
// ISR INT0
void InterruptEX0_ISR() interrupt InterruptEX0{
	isOk=false;
}


// ISR INT1
void InterruptEX1_ISR() interrupt InterruptEX1{
	isOk=true;
}

// ISR TIMER 2
void InterruptTimer2_ISR() interrupt InterruptTimer2{
	TF2 = 0;
	if (isOk==true){
	if(ticks>TIMER_COUNTER){
		switch(curState){
			case LeftDir:
				LedsPort=LedsPort<<1;
				if(LedsPort==128){
					curState=RightDir;
					LedsPort=0xFF;
					led_9=1;
					Delay_s(1);
				}
				break;
			case RightDir:
				LedsPort=LedsPort>>1;
				if(LedsPort==1){
					curState=LeftDir;
					led_9=0;
				}
				break;
			default:
				LedsPort=255;
		}
		ticks=0;
	}else{
		ticks++;
		}
	}
//	TH0=0x3C;
//	TL0=0xB0;
}
	 

void operation(){
	while(1)
		GOTO_SLEEP();
}
