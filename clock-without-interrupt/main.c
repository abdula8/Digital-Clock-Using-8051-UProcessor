#include<reg51.h>
#include "Port.h"
#include "main.h"

void main()
{
	initialization();
	/*
	uncomment the following line to use stop watch mode
	*/
	while(1)
	{
	if(!edit_mode)
		stopWatch(Seg_State[0],Seg_State[1],Seg_State[2],Seg_State[3],Seg_State[4],Seg_State[5]);
	else if(!pause)
		pause_clock();
	else if(dgt_slct==0)
	
		digit_select();
		if(dgt_ncrmnt==0)
		{
			digit_inc();
		}
	
}}



void digit_select()
{
	if (Seg_Control == 0x01)
	{
		Seg_Control = 0x20;
	}
	else{
		Seg_Control = Seg_Control >> 1;
		digit++;
		digit=digit%6;
	}
	delay(1000);
}

void digit_inc()
{
	Seg_State[digit]++;
	display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
	delay(1000);
}

void initialization()
{
	edit_mode = 1;			//INPUT
	digit = 0;					//OUTPUT
	dgt_ncrmnt = 1;			//INPUT
	dgt_slct = 1;				//INPUT
	pause = 1;				//INPUT
	IE = 0x85; 								// 1000 0101 // bydefault INT is enabled to set the clock 
	/* Enabling this digit to start shifting and Seg_Control variable gets a initial value*/
	Seg_Control = 0x01; 			// to enable first Digit in the 6-digit_7-SEG
}


/**
Stop Watch Mode
*/
/*
I! refer to index #1 of the array ==> Seg_State
*/
void stopWatch(tWord I1, tWord I2, tWord I3, tWord I4, tWord I5, tWord I6)
{
	tWord con0, con1, con2, con3, con4, con5, con6;
	con1=I1; con2=I2; con3=I3; con4=I4;
	con5=I5; con6=I6;
	
	//edit_mode = 1;
	
	while(!edit_mode)
	{
		//delay(500);
		Seg_State[0]=con1;
		Seg_State[1]=con2;
		Seg_State[2]=con3;
		Seg_State[3]=con4;
		Seg_State[4]=con5;
		Seg_State[5]=con6;
		
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		con0++;
		if(con0 == 5)// // should be 60 to count second correctly
		{
			con0 = 0;
			con1++;
			Seg_State[0] = con1;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		if ((con1==10))// || (Seg_State[0]==10))  // con1 == 10
		{
			con1 = 0;
			con2++;
			Seg_State[1] = con2;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		if ((con2==6))//|| (Seg_State[1]==3)) // con1 == 6
		{
			con2 = 0;
			con3++;
			Seg_State[2] = con3;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		if((con3==10))//|| (Seg_State[2]==2)) // con1 == 10
		{	
			con3 = 0;
			con4++;
			Seg_State[3] = con4;
		}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
			if ((con4 == 6))//|| (Seg_State[3]==2)) // con1 == 6
			{
				con4 = 0;
				con5++;
				Seg_State[4] = con5;
			}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
			if ((con5 == 10))//|| (Seg_State[4]==2)) // con1 == 10
			{
				con5 = 0;
				con6++;
				Seg_State[5] = con6;
			}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
			if ((con5==4&&con6==2))// || (Seg_State[5]==2&&Seg_State[4]>3))
			{
				con6 = con5 = con4 = con3 = con2 = con1 = 0;
			}
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
	}	
//Seg_Pause();
}

/*  
		display function
		for hour, minutes 
		and seconds
*/
void display(tWord LH, tWord RH, tWord LM, tWord RM, tWord LS, tWord RS)
{
	if(!edit_mode)
	{
		/*  Display Hours  */
		Seg_Control = 0x01;
		if((LH>3) && (RH>=2))
		{
			LH=0;
			RH=0;
		}
		
		Seg_Data = arr[LH%3];
		delay(msec);
		Seg_Control = 0x02;
		Seg_Data = arr[RH%10];
		delay(msec);
		/*  Display Minutes  */
		Seg_Control = 0x04;
		Seg_Data = arr[LM%6];
		delay(msec);
		Seg_Control = 0x08;
		Seg_Data = arr[RM%10];
		delay(msec);
		
		/*  Display Minutes  */
		Seg_Control = 0x10;
		Seg_Data = arr[LS%6];
		delay(msec);
		Seg_Control = 0x20;
		Seg_Data = arr[RS%10];
		delay(msec);
	}
	else
	{
		if (digit == 5)
		{
			/*  Display Hours  */
			Seg_Control = 0x01;
			Seg_Data = arr[LH%3];
			delay(msec);
		}else if(digit == 4)
			{
			Seg_Control = 0x02;
			Seg_Data = arr[RH%10];
			delay(msec);
		}else if(digit == 3)
		{
			/*  Display Minutes  */
			Seg_Control = 0x04;
			Seg_Data = arr[LM%6];
			delay(msec);
		}else if(digit == 2)
			{
			Seg_Control = 0x08;
			Seg_Data = arr[RM%10];
			delay(msec);
		}else if(digit == 1)
			{
			/*  Display Minutes  */
			Seg_Control = 0x10;
			Seg_Data = arr[LS%6];
			delay(msec);
		}else if(digit == 0)
			{
			Seg_Control = 0x20;
			Seg_Data = arr[RS%10];
			delay(msec);
		}
	}
}
void pause_clock()
{
	
	/*  Display Hours  */
		Seg_Control = 0x01;
		Seg_Data = arr[Seg_State[5]%3];
		delay(msec);
	
		Seg_Control = 0x02;
		Seg_Data = arr[Seg_State[4]%10];
		delay(msec);
	
	/*  Display Hours  */
		Seg_Control = 0x04;
		Seg_Data = arr[Seg_State[3]%6];
		delay(msec);
	
		Seg_Control = 0x08;
		Seg_Data = arr[Seg_State[2]%10];
		delay(msec);
	
	/*  Display Hours  */
		Seg_Control = 0x10;
		Seg_Data = arr[Seg_State[1]%6];
		delay(msec);
	
		Seg_Control = 0x20;
		Seg_Data = arr[Seg_State[0]%10];
		delay(msec);
	
}
void delay(int num)
{
	int i;
	int j;
	for(i=0; i<num; i++)
		for(j=0; j<50; j++);
}

void seg_counter()
{
	unsigned int con1, con2, con3, con4, con5, con6;
	con1=0; con2=0; con3=0; con4=0;
	con5=0; con6=0;
	counter = 0;
	
	dgt_slct = 1;
	dgt_ncrmnt = 0;
	while(!dgt_slct)
	{
		if (!dgt_ncrmnt)
		counter = counter + 1;
		
		display(counter,3, 6, 5, 5, 7);

		display(counter+10, 3, 6, 3, 5, 7);

	}
		//seg_reset(); renames to  //Seg_Pause
}

void Seg_Pause()
{
		while(dgt_slct) //dgt_slct
	{
		Seg_Control = 0x01;
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		delay(msec);
		Seg_Control = 0x02;
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		delay(msec);
		Seg_Control = 0x04;
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		delay(msec);
		Seg_Control = 0x08;
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		delay(msec);
		Seg_Control = 0x20;
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		delay(msec);
		Seg_Control = 0x10;
		display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
		delay(msec);
		if (edit_mode)
		{
			Seg_Switch();
		}
	}
	stopWatch(Seg_State[0],Seg_State[1],Seg_State[2],Seg_State[3],Seg_State[4],Seg_State[5]);
}


/*
This function enable one segment to be used in the Seg_Increment() function

How it works:

1- Pressing the EDIT button this function will be called.
2- enable the first SEG if done editing then switch to 2nd one.
3- Pressing the button increment is calling the Seg_Increment() function

==> Enabling specific segment
calling Seg_Display() function to do that
*/
void Seg_Switch()
{
	
	counter  = 0;
	
	//while(edit_sw)
	{
		while(1) 
			if(edit_mode) // seg_SW switch between segments to be edited
			{
				counter++;
				break;
			}
		Seg_Display(counter%6); // to start editing segment one
			/*
		increment segment using its array Seg_State[index]
		*/
		Seg_Increment();
	}
}
/*
Seg_Increment() function to increment according to 
Increment SW, No need to know the target segment
*/

void Seg_Increment()
{
	while(1)
	{
		if (dgt_ncrmnt)
		{
			Seg_State[counter%6]++;
			display(Seg_State[5],Seg_State[4],Seg_State[3],Seg_State[2],Seg_State[1],Seg_State[0]);
			
			break;
		}
	}
}

/*
Seg_Display() function to display on ... the target segment 
to be edited.
*/
void Seg_Display(tWord seg_num)
{
	switch(seg_num)
	{
		case 1:
			Seg_Control = 0x20;
			Seg_Data = arr[Seg_State[counter%6]];
			delay(msec);
			break;
		case 2:
			Seg_Control = 0x10;
			Seg_Data = arr[Seg_State[1]];
			delay(msec);
			break;
		case 3:
			Seg_Control = 0x08;
			Seg_Data = arr[Seg_State[2]];
			delay(msec);
			break;
		case 4:
			Seg_Control = 0x04;
			Seg_Data = arr[Seg_State[3]];
			delay(msec);
			break;
		case 5:
			Seg_Control = 0x02;
			Seg_Data = arr[Seg_State[4]];
			delay(msec);
			break;
		case 6:
			Seg_Control = 0x01;
			Seg_Data = arr[Seg_State[5]];
			delay(msec);
			break;
	}
}