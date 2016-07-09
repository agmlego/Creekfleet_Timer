#include "common.h"
#include "command.h"
#include "flag.h"
#include <Arduino.h>

uint8_t serializeFlagCommand(uint8_t c) {
  if(c == NO_FLAG) {
    return 'x';
  } else {
    return serializeDigit(c);
  }
}

uint8_t serializeDigit(uint8_t c) {
  return c + '0';
}

uint8_t parseFlagCommand(uint8_t c) {
  if(c == 'x') {
    return NO_FLAG;
  } else {
    return parseDigit(c);   
  }
}

uint8_t parseDigit(uint8_t c) {
  return c - '0';
}


void printCommand(Command command) {
  DEBUG_SERIAL.printf("raise: %d, lower: %d, long: %d, short: %d",
    command.raiseFlagPosition,
    command.lowerFlagPosition,
    command.longHornCount, 
    command.shortHornCount); 
}

void sendCommand(Command command) {
  DEBUG_SERIAL.print("Running command: ");
  printCommand(command);
  DEBUG_SERIAL.println();
  
  uint8_t buffer[4];
  buffer[0] = serializeFlagCommand(command.raiseFlagPosition);
  buffer[1] = serializeFlagCommand(command.lowerFlagPosition);
  buffer[2] = serializeDigit(command.longHornCount);
  buffer[3] = serializeDigit(command.shortHornCount);

  for(uint8_t i = 0; i < COMMAND_LENGTH; ++i) {
    while(!CONTROL_SERIAL.availableForWrite());
    CONTROL_SERIAL.write(buffer[i]);
  }
}

boolean isCommandNonEmpty(Command command) {
  return command.raiseFlagPosition != NO_FLAG || 
    command.lowerFlagPosition != NO_FLAG ||
    command.longHornCount > 0 ||
    command.shortHornCount > 0;
}

