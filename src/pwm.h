//pwh.h

#ifndef PWM_H
#define PWM_H
#include <avr/io.h>

//since there are different states the motor can be in, i think there should be motor states used in this code
typedef enum motorStateType_enum{
   forward, reverse, idle
 } motorStateType;

//relized i did more work trying to make the motor(s) but didnt use the changeDutyCycle function as noted in the lab 4 requirements
void initPWM();
void setMotor1Forward();
void setMotor1Reverse();
void setMotor1Off();
void setMotor2Off();

#endif