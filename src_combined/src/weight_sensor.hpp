#include <HX711.h>
#include "Adafruit_ILI9341.h"

void scale_setup();
void calibrate_weight();
int calculate_weight();
float read_weight();