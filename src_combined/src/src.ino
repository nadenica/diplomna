#include "Arduino.h"
#include "hal.h"// include the library code:

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "URTouch.h"

#include <Servo.h>
#include <HX711.h>
#include <AccelStepper.h>


#include "lcd.hpp"
#include "color_sensor.hpp"

#include "weight_sensor.hpp"
#include "servo.hpp"

#include "step_motor.hpp"
#include "ultrasonic.hpp"



// Time tracking variables

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO); // Create a display object and tell the library the pinout for working with graphics.
URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);


Servo servo;
HX711 scale;
AccelStepper stepper(1, PIN_STEP, PIN_DIR);


unsigned long lastBottleTime = 0;
const unsigned long bottleTimeout = 4000; // 4 seconds

void setup() 
{

  Serial.begin(115200);
  setup_lcd(tft, ts);
  servo.attach(PIN_SERVO);
  scale.begin(PIN_HX711_DATA, PIN_HX711_SCK);
  setup_color_sensor(); 
  Serial.println("colorsensor is setup");
  setup_step_motor(stepper); 

  pinMode(PIN_US_TRIG, OUTPUT);
  pinMode(PIN_US_ECHO, INPUT);


  servo_rotate(servo, scale);
  //step_correct_position(stepper);
  Serial.println("setup done");
  
}
int current_bonuses=0;
int all_weight=0;



//0 - blank, 1 - red, 2 - green, 3 - blue 
void loop() 
{
    stepper.move(50);
    Serial.print("moving");
    delay(1000);
    //display_message("If done press the button", tft,  ILI9341_BLUE, 2, 20, 50);
/*
  display_message("Place empty    bottle!", tft, ILI9341_YELLOW, 3 , 20, 50);
  delay(5);

  if(is_there_bottle(scale, tft))
  {
    
    delay(5);
    int a=calculate_weight(scale);
    all_weight+=a;
    if(a>40)//40+ ghrams is the big bottle
      current_bonuses += 2;
    else
      current_bonuses += 1;
  
    int current_color=define_color();

    switch(current_color)
    {
      case 0: display_message("Transperant   bottle", tft, ILI9341_WHITE,3 , 20, 70); break;
      case 1: display_message("Red bottle", tft, ILI9341_RED,3, 20, 70);break;
      case 2: display_message("Green bottle ", tft, ILI9341_GREEN,3, 20, 70);break;
      case 3: display_message("Blue bottle", tft, ILI9341_BLUE,3, 20, 70);break;
    }
    delay(5);
    stepper.move(current_color*50);
    int distance=get_distance();
    Serial.println(distance);

     while(distance<=8)//this is 8 cantimeters
    {
       distance=get_distance();
       Serial.println("Distance");
       Serial.println(distance);
       display_message("Full bucket", tft, ILI9341_RED,3 , 20, 70);
    }

    int IR_value = analogRead(PIN_IR);
    while(IR_value<100)
    {
      display_message("Remove your hand from the pipe!", tft,  ILI9341_RED,3, 20, 50);
      Serial.print("IR = ");
      Serial.println(IR_value);
      IR_value = analogRead(PIN_IR);
      
    }
    servo_rotate(servo, scale);
      Serial.println("servo rotating");
    delay(100);
    stepper.move(-(current_color*50));

    display_message("If done press the button", tft,  ILI9341_ORANGE, 2, 20, 50);
    draw_button(tft);
    
  unsigned long startTime = millis();  // Record the start time

  while (millis() - startTime < 3000)
  {
    
    if (is_button_touched(ts)) 
    {
      Serial.println("printing qr_code");
      generate_QRcode(tft, current_bonuses, all_weight);  
    }
 
  }
  }
*/
}
