#include "pwm.h"
#include <Arduino.h>
#include "motor.h"

// use Timer3 for PWM
//  Clock is 16 MHz
void initPWMTimer3()
{
    // Pin 5 - Output Compare Match Flag
    DDRE |= (1 << DDE3); // assigns pin 5 to output

    // set Fast PWM 10-bit mode, non-inverting
    TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);
    TCCR3B |= (1 << WGM32) | (1 << CS30);

    // set duty cycle by determining OCR3A
    // duty cycle = 25% = 0.25
    // duty cycle = Tpulse/Tperiod = OCR3A/0x3FF
    // OCR3A = 0.25 * 1023 = 255

    OCR3A = 0;
}

void changeDutyCycle(unsigned int result)
{
    if (result < 512)
    {
        OCR3A = 1023 - result * 2; // decrease duty cycle
    }

    else
    {
        OCR3A = 2 * result - 1023; // increase duty cycle
    }

    // read in ADCL and ADCH as 10bit result
    // if 2.5 volts, then no PWM to motor
    /* if (result == (1023 * 0.5)) {
        OCR3A = 0;
       // OCR4A = 0;
    }
    // if less than 2.5 volts, clockwise (Timer 3)
    else if (result < (1023 * 0.5)) {
        setDirection(1);
        OCR3A = (1023* 0.5 - result) * 2;
       // OCR4A = 0;
    }
    // if 0 volts, max RPM clockwise
    else if (result == 0) {
        setDirection(1);
        OCR3A = 1023;
       // OCR4A = 0;
    }
    // if more than 2.5 volts, counterclockwise
    else if (result > (1023 * 0.5)) {
        setDirection(0);
        OCR3A = 0;
        //OCR4A = result;
    }

    // if 5 volts, max RPM counterclockwise
    else if (result == 1023) {
        setDirection(0);
        OCR3A = 0;
        //OCR4A = 1023;
    } */
}
