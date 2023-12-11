#include <Stepper.h>
#include "hal.h"

// Define the number of steps per revolution and create a stepper motor instance

Stepper stepper(STEPS_PER_REVOLUTION, PIN_STEP, PIN_DIR);  // Steps: 200, Step Pin: 8, Direction Pin: 9

void setup()
{
  stepper.setSpeed(60);  // Set the speed (adjust as needed)
}
//0 - blank, 1 - blue, 2 - red, 3 - green 
void loop() 
{
    stepper.step(calculate_steps(COLOR FROM THE COLOR SENSOR));

    delay(1000);
  }
}
