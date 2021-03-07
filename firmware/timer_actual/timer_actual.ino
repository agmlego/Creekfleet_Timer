// outside libs
#include <LiquidCrystal.h>

// Pin definitions
#include "pindefs.h"

LiquidCrystal lcd(LCD_RS,LCD_RW,LCD_E,LCD_DB0,LCD_DB1,LCD_DB2,LCD_DB3,LCD_DB4,LCD_DB5,LCD_DB6,LCD_DB7);

void setup() {
  lcd.begin(20,4);
  lcd.print("");
  pinMode(HORN,OUTPUT);
  pinMode(COMPRESSOR,OUTPUT);
  pinMode(UP_LED,OUTPUT);
  pinMode(DOWN_LED,OUTPUT);
  pinMode(SELECT_LED,OUTPUT);
  pinMode(BACK_LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
