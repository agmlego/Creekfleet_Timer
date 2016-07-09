#include <Arduino.h>
#include "flag.h"
#include "common.h"

void setupFlags() {
  analogWriteResolution(PWM_BITS);
  for(uint8_t i = 0; i < FLAG_COUNT; ++i) {
    setupFlagPins(flags[0]);
  }
  
  //TODO: how to deal with other flags?
  attachFlag0Interrupts(flags[0]);

  //TODO: move flags to correct position
}

Flag getFlag(uint8_t position) {
  return flags[position];
}

void raiseFlag(Flag flag) {
  stopFlag(flag);
  analogWrite(flag.pins.pwm, FLAG_UP_SPEED);
}

void lowerFlag(Flag flag) {
  stopFlag(flag);
  analogWrite(flag.pins.pwm, FLAG_DOWN_SPEED);
}

void stopFlag(Flag flag) {
  analogWrite(flag.pins.pwm, FLAG_STOP_SPEED);
}

void setupFlagPins(Flag flag) {
  FlagPins pins = flag.pins;
  pinMode(pins.pwm, OUTPUT);
  analogWriteFrequency(pins.pwm, PWM_FREQ);
  pinMode(pins.limitUp, INPUT);
  pinMode(pins.limitDown, INPUT);
}

void attachFlag0Interrupts(Flag flag) {
  attachInterrupt(digitalPinToInterrupt(flag.pins.limitUp), onFlag0Top, LOW);
  attachInterrupt(digitalPinToInterrupt(flag.pins.limitDown), onFlag0Bottom, LOW);
}

void onFlag0Top() {
  stopFlag(flags[0]);
}

void onFlag0Bottom() {
  stopFlag(flags[0]);
}
