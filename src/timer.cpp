#include "timer.h"
/*Timer
1.Uses a timer0 to debounce states. Timer 1 to count 10 seconds for
the seven segment display. */


/* Initialize timer 0, you should not turn the timer on here.
 * Delay of 1 us goal. 
* You will need to use CTC mode */
void initTimer0() {
    //TODO!!! Double check the assigned values here. 
    /*
     * OCR0A = (0.000001*16MHz)/(1) = 16
     *
     * checked by Enoch refer to Discord chat
    */
   // CTC SETTING IN THE TIMER REGISTER
	TCCR0A &= ~( (1 << WGM10) | ( 1<< WGM11));
    TCCR0B |= ( 1 << WGM12);
    TCCR0B &= ~ ( 1 << WGM13);

    // sET THE BITS FOR THE prescaller to 001. 
    TCCR0B|=(1 << CS00);
    TCCR0B&=~(1 << CS01);
    TCCR0B&=~(1 << CS02);
    // CTC compare value
    OCR0A=16;
}
//Utilizes timer0 to implement delays for state change. 
void delayUs(unsigned int delay){
    unsigned int delayCnt = 0;
    TCNT0 = 0; //starting the timer at 0 instead of some random junk number
    TIFR0 |= (1 << OCF0A); // set compare flag to start timer
    while (delayCnt < delay) {
        if (TIFR0 & (1 << OCF0A)) { //increment only while the flag is set (timer reached maxval = OCR0A)
            delayCnt++;
            TIFR0 |= (1 << OCF0A);
            //re-start timer. will go to 0 before reaching the if statement above
        }
    }
}

//Used for the SSdisplay Ten second count down. 1 millisecond delay. 
void initTimer1() {
    //TODO!!! Double check the assigned values here. 
    /*
     * OCR1A = (0.001*16MHz)/(64) = 250
     *
     * checked by Enoch refer to Discord chat
    */

   // CTC SETTING IN THE TIMER REGISTER
    TCCR1A&=~(1 << WGM00);
    TCCR1A|=(1 << WGM01);
    TCCR1B&=~(1 << WGM02);

    // sET THE BITS FOR THE prescaller to 011. 
    TCCR1B|=(1 << CS00);
    TCCR1B|=(1 << CS01);
    TCCR1B&=~(1 << CS02);
    // CTC compare value
    OCR1A=250;
}
//Utilizes Timer1 for the SSD clock. 
//must be used 1000 times for each second delay the SSD need to count donw. 
void delayMs(unsigned int delay) {
    unsigned int delayCnt = 0;
    TCNT0 = 0; //starting the timer at 0 instead of some random junk number
    TIFR0 |= (1 << OCF0A); // set compare flag to start timer
    while (delayCnt < delay) {
        if (TIFR0 & (1 << OCF0A)) { //increment only while the flag is set (timer reached maxval = OCR0A)
            delayCnt++;
            TIFR0 |= (1 << OCF0A);
            //re-start timer. will go to 0 before reaching the if statement above
        }
    }
}

