#include "timer.h"
/*Timer
1.Uses a timer0 to debounce states. Timer 1 to count 10 seconds for
the seven segment display. */


/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0() {
    // WGM bits should be 010 for CTC mode
    TCCR0A &= ~( (1 << WGM10) | ( 1<< WGM11));
    TCCR0B |= ( 1 << WGM12);
    TCCR0B &= ~ ( 1 << WGM13);

    // sET THE BITS FOR THE prescaller to 001. 
    TCCR0B|=(1 << CS00);
    TCCR0B&=~(1 << CS01);
    TCCR0B&=~(1 << CS02);
    // CTC compare value
    OCR0A=16; 

    /* //TODO!!! Double check the assigned values here. 
    /*
     * OCR0A = (0.000001*16MHz)/(1) = 16
     *
     * checked by Enoch refer to Discord chat
    */
   // CTC SETTING IN THE TIMER REGISTER
	/*TCCR0A &= ~( (1 << WGM10) | ( 1<< WGM11));
    TCCR0B |= ( 1 << WGM12);
    TCCR0B &= ~ ( 1 << WGM13);

    // sET THE BITS FOR THE prescaller to 001. 
    TCCR0B|=(1 << CS00);
    TCCR0B&=~(1 << CS01);
    TCCR0B&=~(1 << CS02);
    // CTC compare value
    OCR0A=16; */
}
//Utilizes timer0 to implement delays for state change. 
/* void delayMs(unsigned int delay){

    int count = delay;

    // set up prescaler and output compare register value with formula
    // OCR0A = (Td * Clk Freq )/ (Prescaler)
    // 0CR0A = 16000 / Prescaler
    // Td = 1 s, clk freq = 16Mhz, Prescaler = 64
    // OCR0A = 249;
    //set the output compare register OCR0A to 249;

    OCR0A = 249;

    // Turn on clock with prescaler of 64
    TCCR0B  |= (1 << CS00) | (1 << CS01);
    TCCR0B  &= ~ (1 << CS02);

    // Each loop is a 1ms delay, so loop up to count to get a (count) ms delay
    for (int i = 0; i < count; i++){
        // clear 0CF0A flag
        TIFR0 |= (1 << OCF0A);

        // Clear tcnt to restart counting at 0
        TCNT0 = 0;
        
        // Do nothing until the flag goes up (TCNT0 == 249)
        while ( ! (TIFR0 & ( 1 << OCF0A)));
    }
    // turn clock off
    TCCR0B  &= ~ ((1 << CS00) | (1 << CS01) | ( 1 << CS02));    
} */
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
//must be used 1000 times for each second delay the SSD need to count down. 
/* void delayS(unsigned int delay){
    
    //OCR1A = (1 s * 16 MHz) / Prescaler
    //OCR1A = 16000000 / Prescaler
    //Use prescaler of 1025, set OCR1A = 15624
    
    int count = delay;

    OCR1A = 15624;

    TCCR1B &= ~(1 << CS11);
    TCCR1B |= (1 << CS10) | (1 << CS12);

    // Each loop is a 1ms delay, so loop up to count to get a (count) ms delay
    for (int i = 0; i < count; i++){
        // clear 0CF0A flag
        TIFR1 |= (1 << OCF1A);

        // Clear tcnt to restart counting at 0
        TCNT1 = 0;
        
        // Do nothing until the flag goes up (TCNT0 == 249)
        while ( ! (TIFR1 & ( 1 << OCF1A)));
    }
    // turn clock off
    TCCR1B  &= ~((1 << CS10) | (1 << CS11) | ( 1 << CS12));
} */

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

