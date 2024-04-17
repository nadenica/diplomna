
#include "Arduino.h"
#include "hal.h"

//int color_to_steps[] = {0, 50, 100, 150};
static int current_color = 0;
int curr_pos;//nad koq kofa e v momenta
int direction=HIGH;
void setup_step_motor() 
{
  pinMode(PIN_STEP_ENABLE, OUTPUT);
  digitalWrite(PIN_STEP_ENABLE, LOW); // LOW enables the motor driver
  
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
Serial.println("output");
  pinMode(PIN_SWITCH, OUTPUT);
  pinMode(PIN_SWITCH_C, INPUT);
  digitalWrite(PIN_SWITCH, HIGH); //  enables the switch 

  digitalWrite(PIN_DIR, HIGH); // Set the spinning direction clockwise:
  Serial.println("before switch");
  for(int i=0; i<200; i++)
    {
      if(digitalRead(PIN_SWITCH_C)==HIGH)
      {
        Serial.println("buttonpuched");
        break;
      }
      
      digitalWrite(PIN_STEP, HIGH);
      delay(40);
      digitalWrite(PIN_STEP, LOW);
      delay(40);
    }
  digitalWrite(PIN_SWITCH_C, LOW); //  desables the switch 
  //digitalWrite(PIN_STEP_ENABLE, HIGH); // desables the motor driver
  curr_pos=0;
}
int pos(int a)
{
  if(a<0)
    return -a;
  return a;
}

void stepper_motor_move(int bucket)
{
  //digitalWrite(PIN_STEP_ENABLE, LOW); // LOW enables the motor driver
  //  if(bucket<curr_pos)
  //    digitalWrite(PIN_DIR, !direction);
  //  else
    digitalWrite(PIN_DIR, HIGH);
  Serial.println("after direction");
  for(int i=0; i<pos(bucket-curr_pos)*50; i++)
    {
      digitalWrite(PIN_STEP, HIGH);
      delay(50);
      digitalWrite(PIN_STEP, LOW);
      delay(50);
    }
  digitalWrite(PIN_STEP_ENABLE, HIGH); // desables the motor driver
}


