#pragma once
#include <Arduino.h>

#define COMMAND_LENGTH 4


struct Command {
  byte raiseFlagPosition;
  byte lowerFlagPosition;
  byte longHornCount;
  byte shortHornCount;
};

byte parseFlagCommand(byte c);
byte parseDigit(byte c);

void printCommand(Command command);
void sendCommand(Command command);
boolean isCommandNonEmpty(Command command);
byte serializeDigit(byte c);
byte serializeFlagCommand(byte c);
