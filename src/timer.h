//lab 4 timer

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer0();//need to implement this for debouncing states
void delayMs(unsigned int delay);
void initTimer1();//used to count 10 seconds for the seven segment display
void delayS(unsigned int delay);

#endif