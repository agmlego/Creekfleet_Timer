#include <LiquidCrystal.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include "start_sequencer.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void setup(){
	// pulse-per-second interrupt from DS3231
	pinMode(PPS_INT_PIN, INPUT);
	attachInterrupt(PPS_INT, pps_isr, FALLING);
	
	// remote-trigger interrupt from pendant
	pinMode(TRIGGER_INT_PIN, INPUT);
	attachInterrupt(TRIGGER_INT, trigger_isr, FALLING);
	
	// LCD backlight and contrast PWM
	pinMode(LCD_BACKLIGHT, OUTPUT);
	analogWrite(LCD_BACKLIGHT, 127);
	pinMode(LCD_CONTRAST, OUTPUT);
	analogWrite(LCD_CONTRAST, 127);
	
	// button backlight PWM
	pinMode(BUTTON_BACKLIGHT, OUTPUT);
	analogWrite(BUTTON_BACKLIGHT, 127);
	
	// button matrix input
	pinMode(BUTTON_MATRIX, INPUT);
	
	// horn and camera outputs
	pinMode(HORN, OUTPUT);
	pinMode(CAMERA, OUTPUT);
	
	// ambient light sensor
	pinMode(CDS_CELL, INPUT);
	
	// debug serial output
	Serial.begin(115200);
}

void loop()
{
	
}

void pps_isr()
{
	
}

void trigger_isr()
{
	
}