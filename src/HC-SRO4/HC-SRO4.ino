// ########## ALL INCLUDES COME HERE ########## //
#include "hal.h" 
#include "ultrasonic.c"


void setup() {
  Serial.begin(9600);
  InitAllSensors();
}

void loop() {
  int distance = GetDistance(PIN_US_1_TRIG,PIN_US_1_ECHO );
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
  if(distance<20)
    Serial.print("da sloza na displeq 4e kofata e pylna");

  //tozi kod trqbva da se povtori i za drugte 3^^^^^
  delay(1000);
 
}