#pragma once


#include <Arduino.h>

const byte NO_FLAG = 255;
const byte DOWN_POSITION = 1;
const byte UP_POSITION = 2;

struct FlagStatus {
  byte targetPosition;
  bool isMoving;
};
struct FlagPins {
  byte moveUp;
  byte moveDown;
  byte limitUp;
  byte limitDown;
};
struct Flag {
  FlagStatus status;
  FlagPins pins;
};


Flag getFlag(byte position);

void setupFlags();

void raiseFlag(Flag flag);

void lowerFlag(Flag flag);

void stopFlag(Flag flag);

void setupFlagPins(Flag flag);

void attachFlag0Interrupts(Flag flag);

void onFlag0Top();

void onFlag0Bottom();

