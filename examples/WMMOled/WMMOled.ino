#include <Wire.h>
#include "SSD1306Wire.h"
#include "WMMOled.h"
#include <TimeLib.h>


#define SDA 10             //Data pi of In
#define SCL 9              //Clock pin
#define BAUD 9600          //Baud rate
#define ADDRESS 0x3c   //Address  for 128x96 OLED 

unsigned long unix=1634536627;

SSD1306Wire display(ADDRESS, SDA, SCL);
void setup() {
  Serial.begin(BAUD);
  Wire.begin(SDA, SCL); //defining the custom pins for I2C interface
  oledInit(display);
  //display.init();
   Serial.print("Init Done");
  //intializing the dispaly:@Object of SSD1306Wire
}

void loop() 
{
  //Displaying digital clock
  if(millis()%1000==0){
    printTime(display,unix);
    unix++;
  }

}
