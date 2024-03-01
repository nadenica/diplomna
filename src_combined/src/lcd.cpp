#include "Arduino.h"
#include "Adafruit_ILI9341.h" // Software drivers for ILI9341 displays
#include <qrcode.h>
#include "URTouch.h"
#include "hal.h"
#include <string.h>

// Define button dimensions
int buttonX = 20;
int buttonY = 130;
int buttonWidth = 200;
int buttonHeight = 100;

void clear_screen(Adafruit_ILI9341 tft) 
{
  digitalWrite(TFT_CS, LOW);
  tft.fillScreen(ILI9341_BLACK); // Fill the screen with black color
  digitalWrite(TFT_CS, HIGH);
}

void setup_lcd(Adafruit_ILI9341 &tft, URTouch &ts)
{
  digitalWrite(TFT_CS, HIGH);  // Deselect TFT initially
  digitalWrite(t_CS, HIGH);  // Deselect touch screen initially
  
  pinMode(TFT_CS, OUTPUT);
  pinMode(t_CS, OUTPUT);

  tft.begin();
  tft.setRotation(0);
  //setup_lcd(tft, ts);
  
  ts.InitTouch(); 
  ts.setPrecision(PREC_EXTREME); 

  tft.setTextColor(ILI9341_BLUE);
  tft.setTextSize(2);
  tft.setCursor(20, 50);
  tft.print("Hello!");

  Serial.println("lcd is setup");
}

void display_message(const char* message, Adafruit_ILI9341 tft, uint16_t color, int textSize, int cursorX, int cursorY)
{
  digitalWrite(TFT_CS, LOW);  

  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setCursor(cursorX, cursorY);
  tft.print(message);

  delay(2000); 
  
  digitalWrite(TFT_CS, HIGH);  
}

char *qr_code_data(int bonuses, int weight)
{
  char data = new char[50];
  char * name_machine = "my_recycling_machine:)";
  snprintf(data, 50, "%d%s%d", bonuses, name_machine, weight);

  Serial.println("grcode data");
  Serial.println(data);
  return data;
}   
void generate_QRcode(Adafruit_ILI9341 tft, int bonuses, int weight) 
{
 char data[50];
  char * name_machine = "my_recycling_machine:)";
  snprintf(data, 50, "%d%s%d", bonuses, name_machine, weight);
  Serial.println(data);

//  char * data = qr_code_data(bonuses, weight);
  clear_screen(tft);
  digitalWrite(TFT_CS, LOW); 
   
  int qrSize = 3; // Adjust the QR code size based on your requirements
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(qrSize)];

  qrcode_initText(&qrcode, qrcodeData, qrSize, ECC_LOW, data);

  for (int y = 0; y < qrcode.size; y++) 
  {
    for (int x = 0; x < qrcode.size; x++) 
    {
      if (qrcode_getModule(&qrcode, x, y)) 
        tft.fillRect(x * 8, y * 8, 8, 8, ILI9341_WHITE); // Draw white square for QR code module
      else 
        tft.fillRect(x * 8, y * 8, 8, 8, ILI9341_BLACK); // Draw black square for QR code module
      
    }
  }
 // delete [] data;
  digitalWrite(TFT_CS, HIGH); 
  delay(2000);
  clear_screen(tft);
}

bool read_touch(URTouch ts, int &x,int &y)
{
  bool res;
  digitalWrite(t_CS, LOW); 

  if (res=ts.dataAvailable())
  {
    ts.read();
    x = ts.getX();
    y = ts.getY();
          Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.println(y);
  }
  digitalWrite(t_CS, HIGH);
  return res; 
}

bool is_button_touched(URTouch ts) 
{
  int x,y;
  return read_touch(ts, x,y)&&y >= buttonX && y <= buttonX + buttonWidth &&
      x >= buttonY && x <= buttonY + buttonHeight;
}

void draw_button(Adafruit_ILI9341 tft) 
{
  digitalWrite(TFT_CS, LOW);

  tft.fillRect(buttonX, buttonY, buttonWidth, buttonHeight, ILI9341_BLUE);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(5);
  tft.setCursor(buttonX + 25, buttonY + 30);
  tft.print("End");

  digitalWrite(TFT_CS, HIGH);
}





