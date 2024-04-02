//When you can see this in Github and can successfully edit it, please put your name and Net ID
// Author: Carmen Timmer, 
// Net ID: cvtimmer, 
// Date: 3/18/2024
// Assignment:     Lab 4
// if there is a file missing for this lab go ahead and add it in
//----------------------------------------------------------------------//

#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include "pwm.h"
#include "acd.h"
#include "switch.h"


//Initialize states. carried over from lab 2 and 3
typedef enum stateType_enum{
  wait_press, button_press, wait_release, button_release
}  stateType;

volatile stateType state = wait_press;

//new for lab 4
volatile unsigned int motorState = 0;
volatile unsigned int adc_val = 0;

int main(){
  //below I had copied from previous labs by accident but I think it can be usedful for debugging purposes
  Serial.begin(9600);
  sei(); // enable global interrupt

  // initialize here
  initTimer1();
  initADC0();
  initPWM();
  initSwitchPB3();

    while(1){
      switch(state){
        case wait_press:
            break;
          case button_press:
              state = wait_release;
            break;
          case wait_release:
            break;
          case button_release:
          //Serial.println("button_release");

            if (motorState == 2){ //Reverse
              Serial.println("reverse");
              setMotor1Reverse();
              motorState = 0;
              state = wait_press;
              break;
            }
            else if (motorState == 1){ //Forward
              Serial.println("forward");
              setMotor1Forward();
              motorState = 2;
              state = wait_press;
              break;
            }
            else if (motorState == 0){ //Idle
              Serial.println("idle");
              setMotor1Off();
              motorState = 1;
              state = wait_press;
              break;
            }
      break;
    }
  }
    return 0;
}

//for lab4, I think there has a function similar to the ISR below for when we pushed the button to indicate when the motor(s) change direction, what do yall think?



//from previous labs
ISR(PCINT0_vect){
//Serial.println("switch has been HIT");
  if(state == wait_press){
    state = button_press;
  }
  else if(state == wait_release){
    state = button_release;
  }
}