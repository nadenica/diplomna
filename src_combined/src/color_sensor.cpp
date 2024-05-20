#include "Arduino.h"
#include "hal.h"
#include "rgb-hsv.c"
#include "color_sensor.hpp"


const int RedMin = 4;
const int RedMax = 57;
const int GreenMin = 4;
const int GreenMax = 67;
const int BlueMin = 3;
const int BlueMax = 52;

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
float per2freq(int per_us)
{
  return 1000000./per_us;
} 

static int read_color(uint8_t valS2, uint8_t valS3, int min, int max)
{
  digitalWrite(PIN_RGB_S2, valS2);
  digitalWrite(PIN_RGB_S3, valS3);
  int pulse=0;
  for(int i=0;i<100;i++)
  {
    delay(1);
    pulse += pulseIn(PIN_RGB_OUT, LOW, 0);
  }

  float max_f=per2freq(min), min_f=per2freq(max), f=per2freq(pulse/100.);
  //return pulse;

  return map(f, min_f, max_f, 0, 255);
}


char *color_name[] = {"red", "yellow", "green", "cyan", "blue", "magenta", "black", "transparent"};


enum color get_color()
{
   int redValue = read_color(LOW, LOW, RedMin, RedMax);
   Serial.print(" ");
   Serial.print(redValue);

  int greenValue = read_color(HIGH, HIGH, GreenMin, GreenMax);
  Serial.print(" ");
  Serial.print(greenValue);

  int blueValue = read_color(LOW, HIGH, BlueMin, BlueMax);
  Serial.print(" ");
  Serial.println(blueValue);

  
  HSVColor hsv;
  RGBtoHSV(redValue, greenValue, blueValue, &hsv); 
  Serial.print(hsv.h);
  Serial.print(" ");
  Serial.print(hsv.s);
  Serial.print(" ");
  Serial.println(hsv.v);

  int color_ind;

  if(hsv.v<2)
    color_ind=black;
  else if(hsv.s<15)
    color_ind=transparent;
  else
    color_ind=int((hsv.h+30)/60)%6;
  Serial.println(color_name[color_ind]);

  return color_ind;
}
