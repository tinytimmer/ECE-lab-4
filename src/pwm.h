//pwh.h

#ifndef PWM_H
#define PWM_H
#include <avr/io.h>

//relized i did more work trying to make the motor(s) but didnt use the changeDutyCycle function as noted in the lab 4 requirements
// finally added the necessary function for lab 4, but i had to rearrange some stuff in main.cpp
void initPWMTimer3();
void changeDutyCycle(unsigned int result);

#endif