#include "acd.h"
#include <avr/io.h>

//10 bit ADC
//parts I got from lectures and others from looking through github for help

void initADC0(){
    // set reference voltage set to AVCC = 5V output.
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    // determine left/right justified (using RIGHT)
    ADMUX &= ~(1 << ADLAR);

    // specify ADC input channel and mode
    // set ADC0 to single-ended input with MUX[5:0] = 0b000000
    ADCSRB &= ~(1 << MUX5);
    ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2));
    ADMUX &= ~((1<< MUX3) | (1 << MUX4));

    //found this on github for help and this seemed to work from line 21 - 32
    // set Auto Trigger Source Selection
    // use free-running mode ADTS[2:0] = 0b000
    ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));

    // enable ADC and enable auto-triggering
    ADCSRA |= (1 << ADEN) | (1 << ADATE);

    // set ADC clock frequency using prescalar of 128
    // ADC clock frequency is 16MHz divided by prescaler = 125KHz < 200KHz
    // sampling rate = 1 / ((1/125KHz) * 13 clock cylces) = 9615 Hz 
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1);

    // disable ADC0 pin digital input (pin 0 on board)
    DIDR0 |= (1 << ADC0D);

    // start the first ADC conversion
    ADCSRA |= (1 << ADSC);
}