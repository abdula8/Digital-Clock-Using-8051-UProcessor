#ifndef PORTS_H
#define PORTS_H

#define Seg_Control P1
#define Seg_Data P2

sbit edit_mode = P3^0;
sbit digit_select = P3^2;
sbit increment_digit = P3^4;


#endif