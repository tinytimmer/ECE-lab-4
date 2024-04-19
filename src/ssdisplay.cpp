/*Seven Segment display.
Use PORTC pins as outputs to drive the seven segment display
configured in a common cathode mode. 
FOR MORE INFO ON THE 7 Segment Display (5611AS), refer to:   https://components101.com/displays/7-segment-display-pinout-working-datasheet
*/
#include <avr/io.h>
//#include <util/delay.h>
#include "ssdisplay.h"


void initSSDisplay() {
    /* The pins are initialized as outputs in order: 37,  36,  35,  34,  33,  32,  31 -> A, B, C, D, E, F, G
    *                    These are ports, in order: PC0, PC1, PC2, PC3, PC4, PC5, PC6 as outputs. 
    */
   DDRC |= (1 << DDC0) | (1 << DDC1) |  (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5) | (1 << DDC6); 
}


//decided to make this a seperate function to help clear the display directly
void clearSSDisplay(){
    //Empty display, clears/turn off all LEDs in SSDisplay
    PORTC &= ~((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6)); 
}


//Recieves the character to display, running through a switch case to determine what that actually is
//The lights are displayed according to their specification a-g, with the PORTC pins going down alphabeticaly. 
//  Cases for 9-1. (default cause = zero). 
/*
Seven segment configurations for LEDs A-H are as follows (LED H is the decimal point)
{A,B,C,D,E,F,G,H}:
{1,1,1,1,1,1,0,0} //0
{0,1,1,0,0,0,0,0} //1
{1,1,0,1,1,0,1,0} //2
{1,1,1,1,0,0,1,0} //3
{0,1,1,0,0,1,1,0} //4
{1,0,1,1,0,1,1,0} //5
{1,0,1,1,1,1,1,0} //6
{1,1,1,0,0,0,0,0} //7
{1,1,1,1,1,1,1,0} //8
{1,1,1,1,0,1,1,0} //9
*/
void turnOnSSDWithChar(unsigned char num){
  switch (num) {
    case 9:
        PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC5) | (1 << PORTC6); 
        PORTC &= ~((1 << PORTC4));
        break;
    case 8:
        PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6); 
        break;
    case 7:
        PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2); 
        PORTC &= ~((1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6)); 
        break;
    case 6:
        PORTC |= (1 << PORTC0) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6); 
        PORTC &= ~((1 << PORTC1)); 
        break;
    case 5:
        PORTC |= (1 << PORTC0) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC5) | (1 << PORTC6); 
        PORTC &= ~((1 << PORTC1) | (1 << PORTC4)); 
        break;
    case 4:
        PORTC |= (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC5) | (1 << PORTC6); 
        PORTC &= ~((1 << PORTC0) | (1 << PORTC3) | (1 << PORTC4)); 
        break;
    case 3:
        PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC6); 
        PORTC &= ~((1 << PORTC4) | (1 << PORTC5)); 
        break;
    case 2:
        PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6); 
        PORTC &= ~((1 << PORTC2) | (1 << PORTC5)); 
        break;
    case 1: 
        PORTC |= (1 << PORTC1) | (1 << PORTC2); 
        PORTC &= ~((1 << PORTC0) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6)); 
        break;
    default: //Zero. 
        PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5); 
        PORTC &= ~((1 << PORTC6)); 
        break;
  }
}



