#include <HX711.h>
#include "Adafruit_ILI9341.h"

void calibrate_weight(HX711 scale);
int calculate_weight(HX711 scale);
bool is_there_bottle(HX711 scale, Adafruit_ILI9341 tft);