#include "motor.h"
#include <Arduino.h>

void motorSetup()
{
  // Set all the motor control pins to outputs pin 11 & 10 on board
  DDRB |= (1 << DDB5) | (1 << DDB4);
  // DDRH |= (1 << DDH6); use this if we wanted to have another motor
}

void setDirection(unsigned int num)
{
/*     if (num == 1) {
      // clockwise
    PORTB |= (1 << DDB5);
    PORTB &= ~(1 << DDB4);
  }

  else if (num == 2) {
    // counter-clockwise, this doesnt work
    PORTB |= (1 << DDB4);
    PORTB &= ~(1 << DDB5);
  }

  else
  { // motor off
    PORTB &= ~(1 << DDB4);
    PORTB &= ~(1 << DDB5);
  }  */ 
  if (num < 512)
  { // clockwise
    PORTB |= (1 << DDB5);
    PORTB &= ~(1 << DDB4);
  }

  else if (num > 512)
  { // counter-clockwise
    PORTB |= (1 << DDB4);
    PORTB &= ~(1 << DDB5);
  }
  else
  { // motor off
    PORTB &= ~(1 << DDB4);
    PORTB &= ~(1 << DDB5);
  } 

}