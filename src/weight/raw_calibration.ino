// // Arduino Mega HX711 Raw Reading without Library

// #define HX711_DOUT  2   // Connect HX711 data pin to Arduino digital pin 2
// #define HX711_SCK   3   // Connect HX711 clock pin to Arduino digital pin 3

// void setup() {
//   Serial.begin(9600);
//   pinMode(HX711_SCK, OUTPUT);
//   pinMode(HX711_DOUT, INPUT);
// }

// int32_t readHX711() {
//   // Wait for the HX711 to become ready
//   while (digitalRead(HX711_DOUT) == HIGH);

//   // Read 24 bits of data
//   int32_t value = 0;
//   for (int i = 23; i >= 0; --i) {
//     digitalWrite(HX711_SCK, HIGH);
//     value |= (digitalRead(HX711_DOUT) << i);
//     digitalWrite(HX711_SCK, LOW);
//   }

//   // Sign-extend the result
//   if (value & 0x800000) {
//     value |= 0xFF000000;
//   }

//   return value;
// }

// void loop() {
//   int32_t rawValue = readHX711();
//   Serial.print("Raw Value: ");
//   Serial.println(rawValue);
//   delay(5000);
// }

// //calibration factor will be the (reading)/(known weight)