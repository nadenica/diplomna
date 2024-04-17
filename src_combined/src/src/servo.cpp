
#include <Servo.h>
#include "weight_sensor.hpp"
#include "lcd.hpp"
//tuka nesto trqbwa da dobawq s microswitch ili nz
//kak da razbiram da vlezna vyv f-ta za namirane na poziciq kak razbiram 4e toka e sprql

void servo_rotate(Servo servo, HX711 scale)
{
  Serial.println("in servo rotate");
  //servo.write(100);
   for (int pos = 0; pos <= 80; pos += 1)
   {
     servo.write(pos);
     Serial.print(pos);
     Serial.println(" cannot write");
     delay(50);
   }
  Serial.println("before calibrate");
  calibrate_weight(scale);
  delay(1000);  
  Serial.println("before servo returning to first position");
  // Return the servo to 0 degrees
  for (int pos = 80; pos >= 0; pos -= 1)
   {
     servo.write(pos);
     delay(50);
     Serial.print(pos);
     Serial.println(" cannot write");
   }
  //servo.write(-100);
  Serial.println("end of servo funciton");
}

