#pragma once
#include <Arduino.h>

#define COMMAND_LENGTH 4


struct Command {
  uint8_t raiseFlagPosition;
  uint8_t lowerFlagPosition;
  uint8_t longHornCount;
  uint8_t shortHornCount;
};

uint8_t parseFlagCommand(uint8_t c);
uint8_t parseDigit(uint8_t c);

void printCommand(Command command);
void sendCommand(Command command);
boolean isCommandNonEmpty(Command command);
uint8_t serializeDigit(uint8_t c);
uint8_t serializeFlagCommand(uint8_t c);
