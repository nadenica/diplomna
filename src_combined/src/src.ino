#include "hal.h"// include the library code:
#include <LiquidCrystal.h>
#include <Stepper.h>

#include "color_sensor.c"
#include "weight_sensor.c"


Stepper stepper(STEPS_PER_REVOLUTION, PIN_STEP, PIN_DIR);

// Time tracking variables
unsigned long lastBottleTime = 0;
const unsigned long bottleTimeout = 4000; // 4 seconds

void setup() 
{

  Serial.begin(9600);
  SetupColorSensor(); 
  stepper.setSpeed(60);
  
}
//0 - blank, 1 - red, 2 - green, 3 - blue 
void loop() 
{
  lcd.clear();
  lcd.print("Add empty bottle with no cap"); 
  if(is_there_bottle())
  {
    lastBottleTime = millis(); // Update the last bottle time
    //i wake up those other components;
    int current_bonuses=0;
    current_bonuses += calculate_weight();
    lcd.clear();
    lcd.print("Current points: ");
    lcd.print(current_bonuses);

    int current_color=DefineColor();
    stepper.step(calculate_steps(current_color));
    delay(1000);

    lcd.clear();
    lcd.print("Remove your hand");
    int IR_value;
    do
      IR_value = analogRead(A0);
    while(IR_value);

    //motor_ for vyrtene se zavyrta i butilkata pada    
  }

      // Check if 4 seconds have passed without a bottle
  if (millis() - lastBottleTime >= bottleTimeout) 
  {
    //give bonuses
  }

  delay(100);
}