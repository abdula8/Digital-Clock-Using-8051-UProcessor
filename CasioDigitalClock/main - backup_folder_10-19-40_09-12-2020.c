#include <reg52.h>
#include "Interrupt.h"
#include "Ports.h"


#define msec 1

// Typedefs
typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tLong;
typedef enum {last_digit, first_digit} boolean;

/* The digit variable to display on the clock after increment*/
tWord digit;
tWord arr[10]={0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10};
tWord Seg_State[6] = {0, 0, 0, 0, 0, 0};
boolean digit_move = last_digit;

void display(tWord LH, tWord RH, tWord LM, tWord RM, tWord LS, tWord RS);
void delay(tWord num);
void initialization();
void stopWatch(tWord I1, tWord I2, tWord I3, tWord I4, tWord I5, tWord I6);
void flash_digit(tWord digit_flash);

void main(void)
{
	initialization();
	while(1){
		if (!edit_mode)
		{
			stopWatch(Seg_State[0],Seg_State[1],Seg_State[2],Seg_State[3],Seg_State[4],Seg_State[5]);
		}
	}
}

void initialization(){
	
	digit = 0;								//OUTPUT
	increment_digit = 1;			//INPUT
	digit_select = 1;					//INPUT
	IE = 0x85; 								// 1000 0101 // bydefault INT is enabled to set the clock 
	/* Enabling this digit to start shifting and Seg_Control variable gets a initial value*/
	Seg_Control = 0x01; 			// to enable first Digit in the 6-digit_7-SEG
	
}

// ISR INT0
void InterruptEX0_ISR() interrupt InterruptEX0{
	if (Seg_Control == 0x20)
	{
		Seg_Control = 0x01;
		//digit = 1;
	}
	else{
		Seg_Control = Seg_Control << 1;
		digit++;
		digit=digit%6;
	}
	delay(1000);
}

// ISR INT1
void InterruptEX1_ISR() interrupt InterruptEX1{

	//Seg_State[digit%6]++;
	Seg_State[digit]++;
	Seg_Data = arr[Seg_State[digit]%10];
	//Seg_Data = arr[Seg_State[digit]];
	delay(1000);
	
}


void delay(tWord num)
{
	tWord i, j;
	
	for(i=0; i<num; i++)
		for(j=0; j<50; j++);
}


/*  
		display function
		for hour, minutes 
		and seconds
*/
/*
void display(tWord num)
{
	tWord hour, min, sec, temp;
	
	hour = num/3600;
	temp = num%3600;
	min = temp/60;
	sec = temp%60;
	
	Seg_Data = arr[sec%10];
	if (Seg_Control == 0x20)
	{
		Seg_Control = 0x01;
	}
	else{
		Seg_Control = Seg_Control << 1;
	}
}
*/

/*  
		display function
		for hour, minutes 
		and seconds
*/

void display(tWord LH, tWord RH, tWord LM, tWord RM, tWord LS, tWord RS)
{


	/*  Display Hours  */
	Seg_Control = 0x01;
	Seg_Data = arr[LH%10];
	delay(msec);
	Seg_Control = 0x02;
	Seg_Data = arr[RH%10];
	delay(msec);
	
	/*  Display Minutes  */
	Seg_Control = 0x04;
	Seg_Data = arr[LM%10];
	delay(msec);
	Seg_Control = 0x08;
	Seg_Data = arr[RM%10];
	delay(msec);
	
	/*  Display Minutes  */
	Seg_Control = 0x10;
	Seg_Data = arr[LS%10];
	delay(msec);
	Seg_Control = 0x20;
	Seg_Data = arr[RS%10];
	delay(msec);
	
}

void flash_digit(tWord digit_flash)
{
	
	switch(digit_flash)
	{
		case 0x20:
			Seg_Control = digit_flash;
			Seg_Data = arr[digit%10];
			break;
		case 0x10:
			Seg_Control = digit_flash;
			Seg_Data = arr[digit%10];
			break;
		case 0x08:
			Seg_Control = digit_flash;
			Seg_Data = arr[digit%10];
			break;
		case 0x04:
			Seg_Control = digit_flash;
			Seg_Data = arr[digit%10];
			break;
		case 0x02:
			Seg_Control = digit_flash;
			Seg_Data = arr[digit%10];
			break;
		case 0x01:
			Seg_Control = digit_flash;
			Seg_Data = arr[digit%10];
			break;
	}
}


/**
Stop Watch Mode
*/
/*
I! refer to index #1 of the array ==> Seg_State
*/
void stopWatch(tWord I1, tWord I2, tWord I3, tWord I4, tWord I5, tWord I6)
{
	unsigned int con0, con1, con2, con3, con4, con5, con6;
	con1=I1; con2=I2; con3=I3; con4=I4;
	con5=I5; con6=I6;
	
	edit_mode = 1;
	
	while(!edit_mode)
	{
		//delay(500);
		Seg_State[0] = con1;
		Seg_State[1] = con2;
		Seg_State[2] = con3;
		Seg_State[3] = con4;
		Seg_State[4] = con5;
		Seg_State[5] = con6;
		
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		con0++;
		if(con0 == 2) // should be 60 to count second correctly
		{
			con0 = 0;
			con1++;
		Seg_State[0] = con1;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		if (con1 == 10)
		{
			con1 = 0;
			con2++;
			Seg_State[1] = con2;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		if (con2==6)
		{
			con2 = 0;
			con3++;
			Seg_State[2] = con3;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		if(con3==10)
		{	
			con3 = 0;
			con4++;
			Seg_State[3] = con4;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
			if (con4 == 6)
			{
				con4 = 0;
				con5++;
				Seg_State[4] = con5;
			}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
			if (con5 == 10)
			{
				con5 = 0;
				con6++;
				Seg_State[5] = con6;
			}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
			if (con5 == 2 && con6 == 1)
			{
				con6 = con5 = con4 = con3 = con2 = con1 = 0;
			}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
	}
			
}
