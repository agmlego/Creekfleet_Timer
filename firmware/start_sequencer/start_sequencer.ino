#include <LiquidCrystal.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include "start_sequencer.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);
volatile char lcd_buffer0[16];
volatile char lcd_buffer1[16];
time_t cur_time;
time_t start_time;

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
    
    // splash screen
    lcd_buffer0 = "Creekfleet Start";
    lcd_buffer1 = " Sequencer v1.0 ";
    lcd.print(lcd_buffer0);
    lcd.print(lcd_buffer1);
    
    // initialise time values to a sentinel value
    cur_time = -1;
    start_time = -1;
    
    // debug serial output
    Serial.begin(115200);
    Serial.println("I live!");
}

void loop()
{
    cur_time = now();
    
}

void pps_isr()
{
    
}

void trigger_isr()
{
    if(start_time != -1)
    {
        time_t diff = cur_time - start_time;
        lcd_buffer0 = sprintf();
        lcd.print(lcd_buffer0);
    }
}
