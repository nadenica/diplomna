#include "hal.h"
#include "color_sensor.c"

void setup() 
{

  Serial.begin(9600);
  SetupColorSensor(); 
  
}

void loop() 
{
  int masiv[3];
  char res=DefineColor(masiv);
   Serial.print("Red: ");
  Serial.println(masiv[0]);
  Serial.print("Green: ");
  Serial.println(masiv[1]);
  Serial.print("Blue: ");
  Serial.println(masiv[2]);
  Serial.println(res);
  delay(5000);
}