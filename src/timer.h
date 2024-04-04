//lab 4 timer

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer0();//need to implement this for debouncing states
void delayUs(unsigned int delay);
void initTimer1();//used to count 10 seconds for the seven segment display
void delayMs(unsigned int delay);

#endif