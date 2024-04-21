// When you can see this in Github and can successfully edit it, please put your name and Net ID
//  Author: Carmen Timmer,
//  Net ID: cvtimmer,
//  Date: 3/18/2024
//  Assignment:     Lab 4
//  if there is a file missing for this lab go ahead and add it in
//----------------------------------------------------------------------//

#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include "pwm.h"
#include "acd.h"
#include "switch.h"
#include "ssdisplay.h"
#include "motor.h"

// Initialize states. carried over from lab 2 and 3, added in more cases for the number we want to display
typedef enum stateType_enum
{
  wait_press,  button_press,  wait_release,  button_release,  nine,  eight,  seven,  six,  five,  four,  three,  two,  one,  zero
} stateType;

volatile stateType state = wait_press;

// new for lab 4
/* volatile unsigned int motorState = 0;
volatile unsigned int adc_val = 0; */
// Initialize counter for keeping track of SSD counter.
// int cur_count = 9;
volatile boolean activate = true;

int main()
{
  // below I had copied from previous labs by accident but I think it can be usedful for debugging purposes
  Serial.begin(9600);
  sei(); // enable global interrupt

  // initialize here
  initTimer0();
  initTimer1();    // Initialize the SSDisplay timer.
  initSSDisplay(); // Initialize the SSDisplay.
  initSwitchPD0(); // Initialize the switch used for the SSDisplay.
  initPWMTimer3(); // intialize PWM signal using timer 3
  initADC0();
  motorSetup();
  unsigned int result;

  while (1)
  {
    // suggestion from Cole
    // If the system is currently counting down
    // Tried with this suggestion and there were still some issues with the display so I went another route I hope thats ok yall
    /* if(counting) {
      //send the number off to be displayed.
      turnOnSSDWithChar(cur_count);

      //if cur count == 0, end process.
      if (cur_count <= 0) {
        counting = false;
        cur_count = 9;
      }
      else {
        //wait one second.
        delayMs(10000000);

        //increment counter.
        cur_count -= 1;
      }
    } */
    /* result = ADCL;
    result += ((unsigned int)ADCH) << 8;
    changeDutyCycle(result);
    setDirection(result);
    Serial.println(result);
    Serial.flush();
    // Serial.begin(9600); */

    switch (state)
        {
        case wait_press:
          // TODO: Handle ADC conversion to control motor via PWM duty cycle
          result = ADCL;
          //Serial.println("result is " + String(result));
          result += ((unsigned int)ADCH) << 8;
          //Serial.println("result 2 is " + String(result));
          changeDutyCycle(result);
          setDirection(result);
          clearSSDisplay();
          break;

        case button_press:
          delayMs(100);
          state = wait_release;
          break;

        case wait_release:
          break;

        case button_release:
          delayMs(100);
          state = nine;
          break;

          // For each state 9 through 0, desplay the correct number and then wait a second before transitioning to the next state
        case nine:
          // Turn motor off
          // result = (1023 * 0.5);
          // changeDutyCycle(result);
          setDirection(512);
          turnOnSSDWithChar(9);
          delayMs(100000);
          state = eight;
          break;

        case eight:
          turnOnSSDWithChar(8);
          delayMs(100000);
          state = seven;
          break;

        case seven:
          turnOnSSDWithChar(7);
          delayMs(100000);
          state = six;
          break;

        case six:
          turnOnSSDWithChar(6);
          delayMs(100000);
          state = five;
          break;

        case five:
          turnOnSSDWithChar(5);
          delayMs(100000);
          state = four;
          break;

        case four:
          turnOnSSDWithChar(4);
          delayMs(100000);
          state = three;
          break;

        case three:
          turnOnSSDWithChar(3);
          delayMs(100000);
          state = two;
          break;

        case two:
          turnOnSSDWithChar(2);
          delayMs(100000);
          state = one;
          break;

        case one:
          turnOnSSDWithChar(1);
          delayMs(100000);
          state = zero;
          break;

        case zero:
          turnOnSSDWithChar(0);
          delayMs(100000);
          state = wait_press;
          activate = true;
          break;
        }
      } 
    return 0;
  }


// from previous labs
ISR(INT0_vect)
{
  // Wanted to add a flag to tell us if the countdown is currently in progress or not
  if (!activate)
  {
    return;
  }

  // Serial.println("switch has been HIT");
  if (state == wait_press)
  {
    state = button_press;
  }
  else if (state == wait_release)
  {
    state = button_release;
    activate = false;
  }
}
