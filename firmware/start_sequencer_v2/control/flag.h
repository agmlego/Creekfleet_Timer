#pragma once


#include <Arduino.h>

const uint8_t PWM_BITS = 16;
const uint32_t PWM_FREQ = 732422; //732.4218 Hz ideal PWM frequency for 16-bit resolution
const uint8_t NO_FLAG = 255;
const uint8_t DOWN_POSITION = 1;
const uint8_t UP_POSITION = 2;
const uint16_t FLAG_UP_SPEED = 65535;
const uint16_t FLAG_DOWN_SPEED = 0;
const uint16_t FLAG_STOP_SPEED = 32768;

struct FlagStatus {
  uint8_t targetPosition;
  boolean isMoving;
};
struct FlagPins {
  uint8_t pwm;
  uint8_t limitUp;
  uint8_t limitDown;
};
struct Flag {
  FlagStatus status;
  FlagPins pins;
};


Flag getFlag(uint8_t position);

void setupFlags();

void raiseFlag(Flag flag);

void lowerFlag(Flag flag);

void stopFlag(Flag flag);

void setupFlagPins(Flag flag);

void attachFlag0Interrupts(Flag flag);

void onFlag0Top();

void onFlag0Bottom();

