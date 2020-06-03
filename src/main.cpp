#include <Arduino.h>
#include <U8g2lib.h>


// D5, D7, D8
//U8G2_MAX7219_32X8_F_4W_SW_SPI display(U8G2_R0, D5, D7, D8);

U8G2_MAX7219_32X8_F_4W_SW_SPI display(U8G2_R0, /* clock=*/ D5, /* data=*/ D7, /* cs=*/ D8, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);

void setup() {  
  display.begin();  
}

void loop() {   
  display.setDrawColor(2);
  delay(1000);    
  display.setFont(u8g2_font_4x6_mn);
  display.drawPixel(2,2);
  display.sendBuffer();  
}