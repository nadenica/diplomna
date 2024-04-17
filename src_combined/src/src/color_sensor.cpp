#include "Arduino.h"
#include "hal.h"


const int RedMin = 17;
const int RedMax = 300;
const int GreenMin = 20;
const int GreenMax = 345;
const int BlueMin = 18;
const int BlueMax = 280;

void setup_color_sensor()
{
  pinMode(PIN_RGB_S0, OUTPUT);
  pinMode(PIN_RGB_S1, OUTPUT);
  pinMode(PIN_RGB_S2, OUTPUT);
  pinMode(PIN_RGB_S3, OUTPUT);
  //pinMode(PIN_RGB_OE, OUTPUT); 
  pinMode(PIN_RGB_OUT, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(PIN_RGB_S0, HIGH);
  digitalWrite(PIN_RGB_S1, LOW);

  //disabling the sensor at first
   //digitalWrite(PIN_RGB_OE, HIGH);
}

int read_color(uint8_t valS2, uint8_t valS3, int min, int max)
{
  
  
  digitalWrite(PIN_RGB_S2, valS2);
  digitalWrite(PIN_RGB_S3, valS3);
  Serial.println("in read color");
  // Reading the output frequency
  int pulse = pulseIn(PIN_RGB_OUT, LOW, 0);
  return map(pulse, min, max, 255, 0);
}

int get_color()
{
  Serial.println("beforethe maxes");
  int redValue = read_color(LOW, LOW, RedMin, RedMax);
  int greenValue = read_color(HIGH, HIGH, GreenMin, GreenMax);
  int blueValue = read_color(LOW, HIGH, BlueMin, BlueMax);
  Serial.print("RED: ");
  Serial.println(redValue);
  Serial.print("GREEN: ");
  Serial.println(greenValue);
  Serial.print("BLUE: ");
  Serial.println(blueValue);

  int transparentThreshold =180 ;  
  if (redValue > greenValue && redValue > blueValue&& redValue<=100) 
    return 1;
  if (greenValue >= blueValue && greenValue >= redValue) 
    return 2; 
  if (redValue <= transparentThreshold && greenValue <= transparentThreshold && blueValue <= transparentThreshold) 
    return 0;  
  if (blueValue >= redValue && blueValue > greenValue) 
    return 3;



}
int define_color()
{
  // enable the sensor
  //digitalWrite(PIN_RGB_OE, LOW);
  //Serial.println("in define color");
  int res=get_color();
  //digitalWrite(PIN_RGB_OE, HIGH);
  return res;
 
}
