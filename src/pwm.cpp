#include "pwm.h"
#include <Arduino.h>
#include "motor.h"

// use Timer3 for PWM
//  Clock is 16 MHz
void initPWMTimer3()
{
     //Pin 5 - Output Compare Match Flag
    DDRE |= (1<< DDE3); // assigns pin 5 to output


    // set Fast PWM 10-bit mode, non-inverting
    TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);
    TCCR3B |= (1 << WGM32) | (1 << CS30);
    

    //set duty cycle by determining OCR3A
    //duty cycle = 25% = 0.25
    //duty cycle = Tpulse/Tperiod = OCR3A/0x3FF
    //OCR3A = 0.25 * 1023 = 255

    //OCR3A = 0;
}



void changeDutyCycle(unsigned int result)
{
    if (result < 295) { //should be 255, but changed due to physical circuit error
        OCR3A = 1023;
    }
    else if (result >= 295 && result < 512)
    {
        OCR3A = (1023 - result * 2)*2; // decrease duty cycle
        Serial.println("Ocr3A is " + String((1023- 2*result)*2));
    }

    else if (result >= 760) {
        OCR3A = 1023;
    } else {
        OCR3A = (2 * result - 1023)*2; // increase duty cycle
        Serial.println("#2 Ocr3A is " + String((2*result - 1023)*2));
    }
}
