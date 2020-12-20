

#include <reg52.h>
#include "Delay.h"
#include "DataTypes.h"


void Delay_1ms(){
	tWord i;
	for (i=0;i<120;i++);
}

void Delay_ms(tWord x){
	tWord i;
	for(i=0;i<x;i++){
		Delay_1ms();
	}
}

void Delay_s(tWord x)
{
	tWord i;
	for(i=0;i<x;i++){
		Delay_ms(1000);
	}
}


void delay_50ms_Timer(){
	//12MHz
	//65536 - 50000 = 15536 = 0x3cB0
	TMOD=1;
	TH0=0x3c;
	TL0=0xB0;
	TR0=1;
	while(1);
	TR0=0;
	TF0=0;
}