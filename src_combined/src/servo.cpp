
#include <Servo.h>
#include "weight_sensor.hpp"
#include "lcd.hpp"
//tuka nesto trqbwa da dobawq s microswitch ili nz
//kak da razbiram da vlezna vyv f-ta za namirane na poziciq kak razbiram 4e toka e sprql
int pos = 0; 
void servo_rotate(Servo servo, HX711 scale)
{
  for (pos = 0; pos <= 100; pos += 1) {
    servo.write(pos);
    delay(15);
  }

  calibrate_weight( scale);
  delay(1000);  

  // Return the servo to 0 degrees
  for (pos = 100; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(15);
  }
}

