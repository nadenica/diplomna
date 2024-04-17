#include "Arduino.h"
#include "hal.h" 

void trigger_ultrasonic() 
{
  digitalWrite(PIN_US_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_US_TRIG, HIGH);
  delay(10);
  digitalWrite(PIN_US_TRIG, LOW);
}

int get_distance() 
{
  //trigger_ultrasonic();
  digitalWrite(PIN_US_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_US_TRIG, HIGH);
  delay(10);
  digitalWrite(PIN_US_TRIG, LOW);

  unsigned long duration = pulseIn(PIN_US_ECHO, HIGH);//microsec
  float distance = (duration * 0.034) / 2;// Divide by 2 for one-way trip and divide by 29.1 for cm
  
   if (duration == 0) {
    // If the duration is 0, there might be an issue (e.g., disconnected wires)
    Serial.println("Error: No echo received. Check connections.");
  } else {
    // Print the measured distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
     return distance;
  }delay(50);
 
}





