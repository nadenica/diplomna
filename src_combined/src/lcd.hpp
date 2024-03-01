#include <Adafruit_ILI9341.h>
#include "URTouch.h"

void setup_lcd(Adafruit_ILI9341 &tft, URTouch &ts);
void generate_QRcode(Adafruit_ILI9341 tft, int bonuses, int weight);
char *qr_code_data(int bonuses, int weight);
void clear_screen(Adafruit_ILI9341 tft);
bool is_button_touched(URTouch ts);
bool read_touch(URTouch ts, int &x,int &y);
void draw_button(Adafruit_ILI9341 tft);
void display_message(const char* message, Adafruit_ILI9341 tft, uint16_t color, int textSize, int cursorX, int cursorY);
