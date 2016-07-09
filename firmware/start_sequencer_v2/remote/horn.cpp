#include <Arduino.h>
#include "common.h"
#include "horn.h"


void setupHorn() {
  pinMode(HORN_PIN, OUTPUT);
  digitalWrite(HORN_PIN, LOW);
}

void soundHorn(uint16_t lengthMs) {
  digitalWrite(HORN_PIN, HIGH);
  DEBUG_SERIAL.printf("Horn: %d\n",lengthMs);
  delay(lengthMs);
  digitalWrite(HORN_PIN, LOW);
  delay(lengthMs/2);
}

void soundLongHorn() {
  soundHorn(LONG_HORN_MS);
}

void soundShortHorn() {
  soundHorn(SHORT_HORN_MS);
}


