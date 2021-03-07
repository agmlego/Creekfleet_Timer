// outside libs
#include <LiquidCrystal.h>
#include <Bounce.h>
#include <TimeLib.h>
#include <RARGBLED.h>

// Pin definitions
#include "pindefs.h"
#include "horn.h"

// Display constants
const char VERSION[] PROGMEM = "1.0.0";
char SPLASH[81] PROGMEM;
const uint8_t CONTRAST = 64;  // 25% constrast voltage

//UI constants
const uint8_t DEBOUNCE = 10;  // ms of debounce

//Compressor constants
const uint16_t HIGH_PRESSURE = 768;
const uint16_t LOW_PRESSURE = HIGH_PRESSURE - 128;

//UI objects
LiquidCrystal lcd(LCD_RS,LCD_RW,LCD_E,LCD_DB0,LCD_DB1,LCD_DB2,LCD_DB3,LCD_DB4,LCD_DB5,LCD_DB6,LCD_DB7);
RARGBLED lcd_bl(LCD_BL_RED,LCD_BL_GREEN,LCD_BL_BLUE,CommonCathode);
Bounce upButton = Bounce(UP_SWITCH,DEBOUNCE);
Bounce downButton = Bounce(DOWN_SWITCH,DEBOUNCE);
Bounce selectButton = Bounce(SELECT_SWITCH,DEBOUNCE);
Bounce backButton = Bounce(BACK_SWITCH,DEBOUNCE);

void setup() {
  // Set up LCD and backlight
  lcd_bl.off();
  analogWrite(LCD_VO,CONTRAST);
  sprintf(SPLASH,
    "    CreekFleet      "
    "       Start        "
    "     Sequencer      "
    "Version%13s",VERSION);
  lcd.begin(20,4);
  lcd.print(SPLASH);
  lcd_bl.setColor(Color::BLUE);

  // Set pin modes
  pinMode(HORN,OUTPUT);
  pinMode(COMPRESSOR,OUTPUT);
  pinMode(UP_LED,OUTPUT);
  pinMode(DOWN_LED,OUTPUT);
  pinMode(SELECT_LED,OUTPUT);
  pinMode(BACK_LED,OUTPUT);
  pinMode(LCD_BL_RED,OUTPUT);
  pinMode(LCD_BL_GREEN,OUTPUT);
  pinMode(LCD_BL_BLUE,OUTPUT);
  pinMode(UP_SWITCH,INPUT_PULLUP);
  pinMode(DOWN_SWITCH,INPUT_PULLUP);
  pinMode(SELECT_SWITCH,INPUT_PULLUP);
  pinMode(BACK_SWITCH,INPUT_PULLUP);

  // Set up time
  setSyncProvider(Teensy3Clock.get);
  if (timeStatus()!= timeSet){
    lcd.setCursor(0,3);
    lcd.print(F("RTC is not set!     "));
  }else{
    
  }
}

void update_buttons(){
  if (upButton.update()){
    if(upButton.fallingEdge()){
      digitalWrite(UP_LED,HIGH);
    }else{
      digitalWrite(UP_LED,LOW);
    }
  }
  if (downButton.update()){
    if(downButton.fallingEdge()){
      digitalWrite(DOWN_LED,HIGH);
    }else{
      digitalWrite(DOWN_LED,LOW);
    }
  }
  if (selectButton.update()){
    if(selectButton.fallingEdge()){
      digitalWrite(SELECT_LED,HIGH);
    }else{
      digitalWrite(SELECT_LED,LOW);
    }
  }
  if (backButton.update()){
    if(backButton.fallingEdge()){
      digitalWrite(BACK_LED,HIGH);
    }else{
      digitalWrite(BACK_LED,LOW);
    }
  }
}

void update_compressor(){
  uint_16 pressure = analogRead(PRESSURE);
  if(pressure < LOW_PRESSURE){
    digitalWrite(COMPRESSOR,HIGH);
  }
  if(pressure > HIGH_PRESSURE){
    digitalWrite(COMPRESSOR,LOW);
  }
}

void loop() {
  update_buttons();
  update_compressor();
}
