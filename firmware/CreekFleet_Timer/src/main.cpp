#include <Arduino.h>

// outside libs
#include <LiquidCrystal.h>
#include <Bounce2.h>
#include <TimeLib.h>
#include <RARGBLED.h>

// Pin definitions
#include "pindefs.h"
#include "horn.h"

// Display constants
const char VERSION[] PROGMEM = "1.0.0";
char SPLASH[81] PROGMEM;
const uint8_t CONTRAST = 64; // 25% constrast voltage

//UI constants
const uint8_t DEBOUNCE = 10; // ms of debounce

//Compressor constants
const uint16_t HIGH_PRESSURE = 768;
const uint16_t LOW_PRESSURE = HIGH_PRESSURE - 128;
bool COMP_STATE = false;

//UI objects
LiquidCrystal lcd(LCD_RS, LCD_RW, LCD_E, LCD_DB0, LCD_DB1, LCD_DB2, LCD_DB3, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);
RARGBLED lcd_bl(LCD_BL_RED, LCD_BL_GREEN, LCD_BL_BLUE, CommonCathode);
Bounce2::Button upButton = Bounce2::Button();
Bounce2::Button downButton = Bounce2::Button();
Bounce2::Button selectButton = Bounce2::Button();
Bounce2::Button backButton = Bounce2::Button();

char* get_iso_time()
{
  char time_buf[20];
  sprintf(time_buf, "%04d-%02d-%02d %02d:%02d:%02d",
          year(),
          month(),
          day(),
          hour(),
          minute(),
          second());
  return time_buf;
}

void setup()
{
  Serial.begin(115200);
  // Set up LCD and backlight
  lcd_bl.off();
  analogWrite(LCD_VO, CONTRAST);
  sprintf(SPLASH,
          "    CreekFleet      "
          "       Start        "
          "     Sequencer      "
          "Version%13s",
          VERSION);
  lcd.begin(20, 4);
  lcd.print(SPLASH);
  lcd_bl.setColor(COLOR::BLUE);
  Serial.println(SPLASH);

  // Set pin modes
  pinMode(HORN, OUTPUT);
  pinMode(COMPRESSOR, OUTPUT);
  pinMode(UP_LED, OUTPUT);
  pinMode(DOWN_LED, OUTPUT);
  pinMode(SELECT_LED, OUTPUT);
  pinMode(BACK_LED, OUTPUT);
  pinMode(LCD_BL_RED, OUTPUT);
  pinMode(LCD_BL_GREEN, OUTPUT);
  pinMode(LCD_BL_BLUE, OUTPUT);
  Serial.println("Pins configured!");
  upButton.attach(UP_SWITCH, INPUT_PULLUP);
  upButton.interval(DEBOUNCE);
  upButton.setPressedState(LOW);
  downButton.attach(DOWN_SWITCH, INPUT_PULLUP);
  downButton.interval(DEBOUNCE);
  downButton.setPressedState(LOW);
  selectButton.attach(SELECT_SWITCH, INPUT_PULLUP);
  selectButton.interval(DEBOUNCE);
  selectButton.setPressedState(LOW);
  backButton.attach(BACK_SWITCH, INPUT_PULLUP);
  backButton.interval(DEBOUNCE);
  backButton.setPressedState(LOW);
  Serial.println("Buttons configured!");

  // Set up time
  setSyncProvider(Teensy3Clock.get);
  if (timeStatus() != timeSet)
  {
    lcd.setCursor(0, 3);
    lcd.print(F("RTC is not set!     "));
    Serial.println(F("RTC is not set!     "));
  }
  else
  {
    Serial.printf("Got good time! %s",get_iso_time());
  }
}

void update_buttons()
{
  if (upButton.update())
  {
    if (upButton.pressed())
    {
      digitalWrite(UP_LED, HIGH);
      Serial.println("UP pressed");
    }
    else
    {
      digitalWrite(UP_LED, LOW);
    }
  }
  if (downButton.update())
  {
    if (downButton.pressed())
    {
      digitalWrite(DOWN_LED, HIGH);
      Serial.println("DOWN pressed");
    }
    else
    {
      digitalWrite(DOWN_LED, LOW);
    }
  }
  if (selectButton.update())
  {
    if (selectButton.pressed())
    {
      digitalWrite(SELECT_LED, HIGH);
      Serial.println("SELECT pressed");
    }
    else
    {
      digitalWrite(SELECT_LED, LOW);
    }
  }
  if (backButton.update())
  {
    if (backButton.pressed())
    {
      digitalWrite(BACK_LED, HIGH);
      Serial.println("BACK pressed");
    }
    else
    {
      digitalWrite(BACK_LED, LOW);
    }
  }
}

void update_compressor()
{
  uint16_t pressure = analogRead(PRESSURE);
  if (pressure < LOW_PRESSURE && !COMP_STATE)
  {
    COMP_STATE = true;
    digitalWrite(COMPRESSOR, HIGH);
    Serial.println("Turning ON compressor");
  }
  if (pressure > HIGH_PRESSURE && COMP_STATE)
  {
    COMP_STATE = false;
    digitalWrite(COMPRESSOR, LOW);
    Serial.println("Turning OFF compressor");
  }
}

void loop()
{
  update_buttons();
  update_compressor();
  lcd.setCursor(0, 3);
  lcd.print(get_iso_time());
}
