#include "Arduino.h"
#include <HX711.h>
#include "lcd.hpp" 


const float m = -0.0035; // y = mx+b  y= the true weight, x=raw_weight
float b=1744.2975;

void calibrate_weight(HX711 scale)
{
  delay(100);
  Serial.println("in claibration funciton");
  
  if (scale.is_ready()) 
  {
    long rawValue = scale.read(); // Read raw value from the load cell
    b = -(rawValue * m);            // Update the offset based on raw value
    Serial.println("Calibration done. Offset (b) updated.");
  } 
  else
  {
    Serial.println("HX711 not found. Calibration failed.");
  }
  
  delay(1000);
}
int calculate_weight(HX711 scale)
{
  delay(2000);
   if (scale.is_ready()) 
   {
    long rawValue = scale.read(); // Read raw value from the load cell
    float weight =  m*rawValue+b; // Apply calibration factor
    Serial.println(weight);
    return weight;
  } 
  else
    Serial.println("HX711 not found.");
    
}

bool is_there_bottle(HX711 scale, Adafruit_ILI9341 tft)
{
  if (scale.is_ready()) 
  {
    long rawValue = scale.read(); // Read raw value from the load cell
    float weight =  m*rawValue+b; // Apply calibration factor
    Serial.println("weight:");
    Serial.println(weight);
    if(weight<10)
      return false;
    if(weight>60)//the weight of biggest empty cola bottle
    {
      display_message("The bottle is not empty", tft, ILI9341_RED, 3, 55, 20);
      return false;
    }
    return true;

    delay(1000); // Delay for stability
  } 
  else 
    Serial.println("HX711 not found.");
}