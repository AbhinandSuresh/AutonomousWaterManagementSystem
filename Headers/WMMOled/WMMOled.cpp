/*This  library is  created   with necessary functions  which is utilized for initiation of the
   included OLED display on the Motor Controlling Module and also displaying needed informatoin to the user.
   Authuor:Peter Paul */
   
#include <Wire.h>
#include "SSD1306Wire.h"
#include "WMMOled.h" 
//definition of Initialization function
void oledInit(SSD1306Wire display)
{
display.init();
//Display initialization
display.clear();
//Clear displayi
#define WiFi_Logo_width 128
#define WiFi_Logo_height 64
//defning the bitmap of manufacturer logo
const uint8_t WiFi_Logo_bits[]  ={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x1F, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x3C, 0xFC, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x38, 
  0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x33, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x26, 0xFC, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA7, 0xFF, 0xFF, 0xFF, 0x3F, 0x04, 
  0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA7, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x0C, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAF, 0xFF, 
  0xFF, 0xFF, 0x26, 0xFB, 0xFF, 0xFF, 0x8F, 0x09, 0xFC, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x2E, 0xFB, 0xFF, 0xFF, 0x24, 0xF9, 0xFF, 0xFF, 0x87, 0x09, 
  0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x24, 0xF1, 0xFF, 0xFF, 0x24, 0xF5, 
  0xFF, 0xFF, 0x83, 0x1F, 0xE0, 0x1F, 0x00, 0x00, 0x00, 0x60, 0x84, 0x95, 
  0xFD, 0xFF, 0x28, 0xD5, 0xFF, 0xFF, 0x84, 0x3F, 0xC0, 0x1F, 0x00, 0x00, 
  0x00, 0x00, 0x85, 0x94, 0x00, 0x00, 0x28, 0x95, 0xFC, 0x3F, 0xA7, 0x3F, 
  0xC0, 0x1F, 0x00, 0x00, 0x00, 0xE0, 0x99, 0x14, 0xE0, 0xFF, 0x1A, 0x95, 
  0x08, 0xC0, 0x37, 0x3F, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0xF0, 0xD9, 0x24, 
  0xFF, 0xFF, 0x5A, 0x95, 0xF1, 0x7F, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 
  0x87, 0xFF, 0xD9, 0xA4, 0xFF, 0xFF, 0x5B, 0x15, 0xFD, 0x3F, 0x00, 0x00, 
  0xC0, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0xDF, 0xEC, 0xFF, 0xFF, 0x5B, 0x05, 
  0xFF, 0x3F, 0x00, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x5B, 0xA5, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0xFF, 
  0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5B, 0xA4, 0xFF, 0xFF, 0xFF, 0x07, 
  0xC0, 0xFF, 0xFF, 0xFF, 0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDB, 0xEE, 
  0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0xFF, 0x00, 0xFF, 0x87, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xDF, 0xFE, 0xFF, 0xFF, 0xFF, 0x03, 0xC0, 0x3F, 0x00, 0xFC, 
  0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x23, 
  0xC0, 0x1F, 0x00, 0xF8, 0x87, 0xC7, 0x7F, 0xFC, 0x01, 0xC0, 0xFF, 0x0F, 
  0xF8, 0xFF, 0xFF, 0x21, 0xC0, 0x0F, 0x18, 0xF0, 0x87, 0xC3, 0x7F, 0xFC, 
  0x01, 0x80, 0xFF, 0x03, 0xE0, 0xFF, 0xFF, 0x30, 0xC0, 0x07, 0xFE, 0xE0, 
  0x87, 0xC3, 0x7F, 0xFC, 0x01, 0x00, 0xFF, 0x03, 0xE0, 0xFF, 0x7F, 0x38, 
  0xC0, 0x87, 0xFF, 0xC1, 0x87, 0xC3, 0x7F, 0xFC, 0xF1, 0x0F, 0xFF, 0xE1, 
  0xC3, 0xFF, 0x3F, 0x3C, 0xC0, 0xC3, 0xFF, 0xC3, 0x87, 0xC3, 0x7F, 0xFC, 
  0xF1, 0x1F, 0xFE, 0xF0, 0x87, 0xFF, 0x1F, 0x3E, 0xC0, 0xC3, 0xFF, 0x87, 
  0x87, 0xC3, 0x7F, 0xFC, 0xF1, 0x1F, 0xFE, 0xF0, 0x8F, 0xFF, 0x0F, 0x3F, 
  0xC0, 0xC3, 0xFF, 0x87, 0x87, 0xC3, 0x7F, 0xFC, 0xF1, 0x1F, 0xFE, 0xF8, 
  0x8F, 0xFF, 0x87, 0x3F, 0xC0, 0xE1, 0xFF, 0x87, 0x87, 0xC3, 0x7F, 0xFC, 
  0xF1, 0x1F, 0xFE, 0x00, 0x80, 0xFF, 0xC3, 0x3F, 0xC0, 0xE1, 0xFF, 0x8F, 
  0x87, 0xC3, 0x7F, 0xFC, 0xF1, 0x1F, 0x7E, 0x00, 0x80, 0xFF, 0xE1, 0x3F, 
  0xC0, 0xE1, 0xFF, 0x8F, 0x87, 0xC3, 0x7F, 0xFC, 0xF1, 0x1F, 0x7E, 0x00, 
  0x80, 0xFF, 0xF0, 0x3F, 0xC0, 0xE1, 0xFF, 0x87, 0x87, 0xC3, 0x7F, 0xFC, 
  0xF1, 0x1F, 0x7E, 0xF8, 0xFF, 0x7F, 0xF8, 0x3F, 0xC0, 0xE1, 0xFF, 0x87, 
  0x87, 0xC3, 0x7F, 0xFC, 0xF1, 0x1F, 0x7E, 0xF8, 0xFF, 0x3F, 0xFC, 0x3F, 
  0xC0, 0xC3, 0xFF, 0x87, 0x87, 0xC3, 0x7F, 0xFC, 0xF1, 0x1F, 0xFE, 0xF8, 
  0xFF, 0x3F, 0xFE, 0x3F, 0xC0, 0xC3, 0xFF, 0x83, 0x87, 0xC7, 0x7F, 0xFC, 
  0xF1, 0x1F, 0xFE, 0xF0, 0xFF, 0x3F, 0xFE, 0x3F, 0xC0, 0x83, 0xFF, 0xC3, 
  0x87, 0xC7, 0x7F, 0xFC, 0xF1, 0x1F, 0xFE, 0xF0, 0xFF, 0x1F, 0xFE, 0x3F, 
  0xC0, 0x07, 0xFF, 0xC1, 0x87, 0x87, 0x7F, 0xFC, 0xF1, 0x1F, 0xFE, 0xE1, 
  0xFF, 0x1F, 0xFE, 0x3F, 0xC0, 0x0F, 0x7E, 0xE0, 0x87, 0x07, 0x7F, 0xFC, 
  0xF1, 0x1F, 0xFE, 0x81, 0x8F, 0x1F, 0x00, 0x00, 0xC0, 0x0F, 0x00, 0xF0, 
  0x87, 0x0F, 0x00, 0xFC, 0xF1, 0x1F, 0xFE, 0x03, 0x80, 0x1F, 0x00, 0x00, 
  0xC0, 0x1F, 0x00, 0xF8, 0x87, 0x1F, 0x00, 0xFC, 0xF1, 0x1F, 0xFE, 0x0F, 
  0x80, 0x1F, 0x00, 0x00, 0xC0, 0x7F, 0x00, 0xFC, 0x87, 0x7F, 0x00, 0xFE, 
  0xFF, 0x7F, 0xFF, 0x3F, 0xF0, 0xBF, 0xFF, 0x3F, 0xE0, 0xFF, 0x01, 0xFF, 
  0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 
  0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 
  0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1C, 0xFE, 0xF8, 0xE3, 
  0x6F, 0x7F, 0xFB, 0xC7, 0xBF, 0xFF, 0xF9, 0x8F, 0xBF, 0x3F, 0xFE, 0x30, 
  0x3C, 0x7F, 0xFE, 0xFB, 0x6F, 0x7F, 0xFA, 0x93, 0xBF, 0xFF, 0xF6, 0xE7, 
  0xBF, 0xBF, 0xFF, 0x3E, 0xBC, 0x7F, 0xFC, 0xFD, 0x0F, 0x7F, 0xF8, 0xBB, 
  0xBF, 0x7F, 0xEF, 0xF7, 0xBF, 0x3F, 0xFF, 0x38, 0xBC, 0x7F, 0xFE, 0xF9, 
  0x6F, 0x7F, 0xF9, 0xBB, 0xBF, 0xFF, 0xE6, 0xB7, 0xBF, 0xBF, 0xFF, 0x37, 
  0xBC, 0x7F, 0xF8, 0xE3, 0x6F, 0x7F, 0xFB, 0xC7, 0x3F, 0xFE, 0xF0, 0x8F, 
  0xBF, 0x3F, 0xFE, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00,
  };

display.drawXbm(0, 0, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
//displaying the logo
display.display();
 }