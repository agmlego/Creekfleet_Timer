#include "flag.h"
#include "horn.h"
#include "compressor.h"
#include "common.h"
#include "command.h"

Command currentCommand;

byte buf[COMMAND_LENGTH];
int bufPos=0;

void setup() {

  CONTROL_SERIAL.begin(9600);
  DEBUG_SERIAL.begin(9600);

  delay(1000);
  
  //setupFlags();
  setupHorn();
  setupCompressor();
  

 

  //no initial command
  currentCommand.raiseFlagPosition = NO_FLAG;
  currentCommand.lowerFlagPosition = NO_FLAG;
  currentCommand.longHornCount = 0;
  currentCommand.shortHornCount = 0;
  
}

void loop() {

  recieveCommand();

  //processFlagCommand();

  //TODO: only if no flags are moving
  if(true) {
     processHornCommand();
  }

  if(isCommandNonEmpty(currentCommand)) {
    DEBUG_SERIAL.print("next command: ");
    printCommand(currentCommand);
    DEBUG_SERIAL.println();
  }
}

void recieveCommand() {
  while(CONTROL_SERIAL.available()) {
    buf[bufPos++]=CONTROL_SERIAL.read();
    if(bufPos == COMMAND_LENGTH) {
      Command newCommand;
      newCommand.raiseFlagPosition = parseFlagCommand(buf[0]);
      newCommand.lowerFlagPosition = parseFlagCommand(buf[1]);
      newCommand.longHornCount = parseDigit(buf[2]);
      newCommand.shortHornCount = parseDigit(buf[3]);
      currentCommand = newCommand;
      bufPos = 0;

      DEBUG_SERIAL.print("Recieved Command: ");
      printCommand(currentCommand);
      DEBUG_SERIAL.println();
    }
  }
}

void processFlagCommand() {
  if(currentCommand.raiseFlagPosition != NO_FLAG) {
    raiseFlag(getFlag(currentCommand.raiseFlagPosition));
    currentCommand.raiseFlagPosition = 0;
  }
  if(currentCommand.lowerFlagPosition != NO_FLAG) {
    lowerFlag(getFlag(currentCommand.lowerFlagPosition));        
    currentCommand.lowerFlagPosition = 0;
  }
}

void processHornCommand() {
  if(currentCommand.longHornCount > 0) {
      //Nothing is moving, sound long horn
      soundLongHorn();
      currentCommand.longHornCount -= 1;
    } else if (currentCommand.shortHornCount > 0) {
      soundShortHorn();
      currentCommand.shortHornCount -= 1;
    }
}


