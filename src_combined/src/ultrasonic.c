#include "Arduino.h"
#include "hal.h" 
#include "ultrasonic.h"

void InitUltrasonicSensor(int pin_trigger, int pin_echo) 
{
    pinMode(pin_trigger, OUTPUT);
    //digitalWrite(pin_trigger, LOW);
    pinMode(pin_echo, INPUT);
}
void InitAllSensors() 
{
    InitUltrasonicSensor(PIN_US_1_TRIG, PIN_US_1_ECHO);
    //InitUltrasonicSensor(PIN_US_2_TRIG, PIN_US_2_ECHO);
    //InitUltrasonicSensor(PIN_US_3_TRIG, PIN_US_3_ECHO);
    //InitUltrasonicSensor(PIN_US_4_TRIG, PIN_US_4_ECHO);
}
void TriggerUltrasonic(int pin_trigger) 
{
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trigger, HIGH);
  delay(DELAY_US_TRIG);
  digitalWrite(pin_trigger, LOW);
}

int GetDistance(int pin_trigger,int pin_echo) 
{
  TriggerUltrasonic(pin_trigger);
  int duration = pulseIn(pin_echo, HIGH, 20000);
  int distance = (duration/2)/29.1;// Divide by 2 for one-way trip and divide by 29.1 for cm

  return distance;
}





