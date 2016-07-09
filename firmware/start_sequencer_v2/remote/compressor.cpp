#include "compressor.h"
#include "common.h"
#include "Bounce.h"

uint8_t switchState = 2;

IntervalTimer debounceTimer;



void setupCompressor() {
  pinMode(COMPRESSOR_PIN, OUTPUT);
  pinMode(PRESSURE_SWITCH, INPUT_PULLUP);
  stopCompressor();
  

  attachInterrupt(digitalPinToInterrupt(PRESSURE_SWITCH), checkCompressor, CHANGE);

    
  checkCompressor();

}

void checkCompressor() {
  switchState = digitalRead(COMPRESSOR_PIN);
  debounceTimer.begin(compressorDebounce, DEBOUNCE_US);
}

void compressorDebounce() {
  debounceTimer.end();

  uint8_t newState = digitalRead(COMPRESSOR_PIN);
  if(switchState == newState) {
    if(switchState == LOW) {
      startCompressor();
    } else if(switchState == HIGH) {
      stopCompressor();
    }
  }
  noInterrupts();
  switchState = newState;
  interrupts();
}



void startCompressor() {
  digitalWrite(COMPRESSOR_PIN, HIGH);
  DEBUG_SERIAL.println("Compressor on");
}

void stopCompressor() {
  digitalWrite(COMPRESSOR_PIN, LOW);
  DEBUG_SERIAL.println("Compressor off");
}

