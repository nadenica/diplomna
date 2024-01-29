#include "Arduino.h"
#include "hal.h"
#include "calibration.c"
#include "RGB-HSV.h"

const int RedMin = 17;
const int RedMax = 292;
const int GreenMin = 20;
const int GreenMax = 345;
const int BlueMin = 18;
const int BlueMax = 280;

void SetupColorSensor()
{
  pinMode(PIN_RGB_S0, OUTPUT);
  pinMode(PIN_RGB_S1, OUTPUT);
  pinMode(PIN_RGB_S2, OUTPUT);
  pinMode(PIN_RGB_S3, OUTPUT);

  pinMode(PIN_RGB_OUT, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(PIN_RGB_S0, HIGH);
  digitalWrite(PIN_RGB_S1, LOW);
  
}

int ReadColor(uint8_t valS2, uint8_t valS3, int min, int max)
{
  digitalWrite(PIN_RGB_S2, valS2);
  digitalWrite(PIN_RGB_S3, valS3);
  
  // Reading the output frequency
  int pulse = pulseIn(PIN_RGB_OUT, LOW, 0);
  return map(pulse, min, max, 255, 0);
}

int DefineColor()
{
  int redValue = ReadColor(LOW, LOW, RedMin, RedMax);
  int greenValue = ReadColor(HIGH, HIGH, GreenMin, GreenMax);
  int blueValue = ReadColor(LOW, HIGH, BlueMin, BlueMax);

  // Calculate a threshold value for transparency
  int transparentThreshold = 140;
   
 if (redValue <= transparentThreshold && greenValue <= transparentThreshold && blueValue <= transparentThreshold) 
    return 0;
  if (redValue > greenValue && redValue > blueValue) 
    return 1;
  if (greenValue >= blueValue && greenValue > redValue) 
    return 2;
  if (blueValue >= redValue && blueValue > greenValue) 
    return 3;
  
}
