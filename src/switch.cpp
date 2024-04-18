#include "switch.h"
#include <avr/io.h>
/*Switch
1.Uses a switch to turn the motor off.
2.The external interrupt must be of the type INTn (not PCINT) that is
used for switch debouncing. The interrupt sense control should be
configured for any logical change on INTn generates an interrupt
request.
3.PORTD0 should be used for this external interrupt.
4.The external interrupt should not work while the timer and seven
segment display is counting down from 9 secs to 0. */

//Utilizes the D0 port to use the INT0 interrupt. 
void initSwitchPD0(){
  // Initializes pull-up resistor on PD0 (pin 21 on board) and sets it into input mode
  PORTD |= (1 << PORTD0); // set direction for input. 
  DDRD &= ~(1 << DDD0);   // enable the pullup resistor for stable input. 

  //enable the external interrupt INT0 so that any edge of the signal generates asynchronously an 
  // interrupt. to do that we have to enable the EICRA register and bits ISC00=1, and ISC01=0.
  EICRA &= ~(1 << ISC01); 
  EICRA |= (1 << ISC00); 

  //enable the external interrupt mask register so that INT0 bit is enabled for interrupts. 
  EIMSK |= (1 << INT0);
}
