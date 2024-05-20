#include "Arduino.h"
#include "hal.h"// include the library code:

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "URTouch.h"

#include <Servo.h>
#include <HX711.h>

#include "lcd.hpp"
#include "color_sensor.hpp"

#include "weight_sensor.hpp"
#include "servo.hpp"

#include "ultrasonic.hpp"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO); // Create a display object and tell the library the pinout for working with graphics.
URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

Servo servo;
Servo bottom_servo;

unsigned long lastBottleTime = 0;
const unsigned long bottleTimeout = 4000; // 4 seconds
int servo_min_micr=630;
int servo_max_micr=2320;
void setup() 
{  
  Serial.begin(115200);
  Serial.println("been reseting");
  setup_lcd(tft, ts);
  scale_setup();
  servo.attach(PIN_SERVO_TOP, servo_min_micr, servo_max_micr);
  bottom_servo.attach(PIN_SERVO_BOTTOM, servo_min_micr, servo_max_micr);
 
  servo_rotate(servo);
  Serial.println("servo done");

  setup_color_sensor(); 
  
  Serial.println("colorsensor is setup");
 
  pinMode(PIN_US_TRIG, OUTPUT);
  pinMode(PIN_US_ECHO, INPUT);
  Serial.println("setup done");
  
}
int current_bonuses=0;
float all_weight=0;
int bucket[] = {1 , 2, 2, 3, 3, 1, 1, 0 };

bool is_there_bottle()
{
  float weight =  read_weight(); // Apply calibration factor
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
//0 - blank, 1 - red, 2 - green, 3 - blue 
void loop() 
{

  display_message("Place empty    bottle!", tft, ILI9341_YELLOW, 3 , 20, 50);
  Serial.println("place bottle");
  
  if(is_there_bottle())
  {
    delay(5);
    int a=calculate_weight();
    all_weight+=a;
    if(a>40)//40+ ghrams is the big bottle
      current_bonuses += 2;
    else
      current_bonuses += 1;
  
    color c=get_color();
    display_message(color_name[c],tft, ILI9341_WHITE,3 , 20, 70);
    delay(5);

    int distance=get_distance();
    Serial.println(distance);
  
     while(distance<=8)
    {
       distance=get_distance();
       Serial.println("Distance");
       Serial.println(distance);
       display_message("Full bucket", tft, ILI9341_RED,3 , 20, 70);
    }

    int IR_value = analogRead(PIN_IR);
    while(IR_value<40)
    {
      display_message("Remove your hand from the pipe!", tft,  ILI9341_RED,3, 20, 50);
      
      Serial.print("IR = ");
      Serial.println(IR_value);
      IR_value = analogRead(PIN_IR);
      
    }
    
    Serial.print("no hand in the pipe");
    rotate_to_angle(bottom_servo, bucket[c]*90);
    servo_rotate(servo);
    delay(100);
    
    display_message("If done press the button", tft,  ILI9341_ORANGE, 2, 20, 50);
    draw_button(tft);
   
  unsigned long startTime = millis();

  while (millis() - startTime < 3000)
  {
    if (is_button_touched(ts)) 
    {
      Serial.println("printing qr_code");
      generate_QRcode(tft, current_bonuses, all_weight);  
      current_bonuses=0;
    }
  }
  }
  Serial.print("Current bonuses:");
  Serial.println(current_bonuses);
}
