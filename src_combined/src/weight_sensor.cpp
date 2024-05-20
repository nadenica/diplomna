#include "Arduino.h"
#include <HX711.h>
#include "lcd.hpp" 
#include "hal.h"

HX711 scale;
const float m = -0.0060579; // y = mx+b  y= the true weight, x=raw_weight
float b;

void scale_setup()
{
  scale.begin(PIN_HX711_DATA, PIN_HX711_SCK);
  Serial.println("scale setup");
}
float read_raw()
{
  float res=0;
  for(int a=0;a<20;a++)
  {
    res += scale.read();
  }
  return res/20;
}

void calibrate_weight()
{
  Serial.println("in claibration funciton");
  
  while (!scale.is_ready()) 
    delay(500);
  delay(500);
  float rawValue = read_raw(); // Read raw value from the load cell
  Serial.println("rawvalue from calib");
  Serial.println(rawValue);
  b = -(rawValue * m);            // Update the offset based on raw value
  Serial.println("Calibration done. Offset (b) updated.");
}
int calculate_weight()
{
  delay(1000);
   if (scale.is_ready()) 
   {
    long rawValue = read_raw(); // Read raw value from the load cell
    float weight =  m*rawValue+b; // Apply calibration factor
    Serial.println(weight);
    return weight;
  } 
  else
    Serial.println("HX711 not found.");
    
}
float read_weight()
{
  return m*read_raw()+b;
}
