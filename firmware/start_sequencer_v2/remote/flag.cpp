#include <Arduino.h>
#include "flag.h"
#include "common.h"

void setupFlags() {
  
  for(int i = 0; i < FLAG_COUNT; ++i) {
    setupFlagPins(flags[0]);
  }
  
  //TODO: how to deal with other flags?
  attachFlag0Interrupts(flags[0]);

  //TODO: move flags to correct position
}

Flag getFlag(byte position) {
  return flags[position];
}

void raiseFlag(Flag flag) {
  stopFlag(flag);
  digitalWrite(flag.pins.moveUp, HIGH);
}

void lowerFlag(Flag flag) {
  stopFlag(flag);
  digitalWrite(flag.pins.moveDown, HIGH);
}

void stopFlag(Flag flag) {
  digitalWrite(flag.pins.moveUp, LOW);
  digitalWrite(flag.pins.moveDown, LOW);
}

void setupFlagPins(Flag flag) {
  FlagPins pins = flag.pins;
  pinMode(pins.moveUp, OUTPUT);
  pinMode(pins.moveDown, OUTPUT);
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
