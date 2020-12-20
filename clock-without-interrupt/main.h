/*------------------------------------------------------------*-

								Main.H (v1.00)

-------------------------------------------------------------

				'Project Header' for project HOUR

-*------------------------------------------------------------*/


#ifndef _MAIN_H
#define _MAIN_H


// Typedefs
typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tLong;


/* msec: milli second constant to delay */
#define msec 1

tWord arr[10]={0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0x00,0x10};
tWord counter;
tWord Seg_State[6] = {0, 0, 0, 0, 0, 0};
tWord Seg_Switch_Counter;
tWord digit=0;


void display(unsigned int LH, unsigned int RH, unsigned int LM, unsigned int RM, unsigned int LS, unsigned int RS);
void delay(int num);
void seg_counter();
void stopWatch(tWord I1, tWord I2, tWord I3, tWord I4, tWord I5, tWord I6);
void Seg_Pause();
void Seg_Display(tWord seg_num);
void Seg_Switch(); /* switch between segments to increase its value using increment function */
void Seg_Increment();
void pause_clock();
void digit_select();
void initialization();
void digit_inc();


#endif