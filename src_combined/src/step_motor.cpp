
#include "Arduino.h"
#include <AccelStepper.h>
#include "hal.h"

//int color_to_steps[] = {0, 50, 100, 150};
static int current_color = 0;

void setup_step_motor(AccelStepper &stepper) 
{
   
  stepper.setMaxSpeed(1000);      // desired maximum speed in steps per second
  stepper.setAcceleration(500);   // desired acceleration in steps per second^2

  pinMode(PIN_STEP_ENABLE, OUTPUT);
  digitalWrite(PIN_STEP_ENABLE, LOW); // LOW enables the motor driver

   pinMode(PIN_SWITCH, INPUT);
   pinMode(PIN_SWITCH_C, OUTPUT);
  digitalWrite(PIN_SWITCH_C, HIGH); //  enables the switch 

  for(int i=0; i<200 && digitalRead(PIN_SWITCH)==LOW; i++)
    stepper.move(i);

  stepper.move(-175); //to go back to the first bucket and directly above it
  digitalWrite(PIN_SWITCH_C, LOW); //  desables the switch 
  digitalWrite(PIN_STEP_ENABLE, HIGH); // desables the motor driver
}


