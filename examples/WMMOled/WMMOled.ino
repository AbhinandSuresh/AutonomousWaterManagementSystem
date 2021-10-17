#include <Wire.h>
#include "SSD1306Wire.h"
#include "WMMOled.h"

#define SDA 10             //Data pi of In
#define SCL 9              //Clock pin
#define BAUD 9600          //Baud rate
#define ADDRESS 0x3c   //Address  for 128x96 OLED 

SSD1306Wire display(ADDRESS, SDA, SCL);

void setup() {
  Serial.begin(BAUD);
  Wire.begin(SDA, SCL); //defining the custom pins for I2C interface
  
  oledInit(display);
  //intializing the dispaly:@Object of SSD1306Wire
}

void loop() {
}
