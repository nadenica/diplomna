
#include <Servo.h>
#include "weight_sensor.hpp"
#include "servo.hpp"
#include "lcd.hpp"
//tuka nesto trqbwa da dobawq s microswitch ili nz
//kak da razbiram da vlezna vyv f-ta za namirane na poziciq kak razbiram 4e toka e sprql
int minAngle = 0;  // Minimum angle (0°)
int maxAngle = 270;  // Maximum angle (270°)

int min_micr=630;
int max_micr=2320;

void servo_rotate(Servo servo)
{
  Serial.println("in servo rotate");
  servo.write(100);
  delay(3000); 
  calibrate_weight();
  Serial.println("back to 0");
  servo.write(0); 
  delay(3000); 
}


void rotate_to_angle(Servo servo, int angle)
{
  int pulseWidth = map(angle, minAngle, maxAngle, min_micr, max_micr);
  servo.writeMicroseconds(pulseWidth);
}
