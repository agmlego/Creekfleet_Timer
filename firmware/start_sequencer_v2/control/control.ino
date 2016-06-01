#include "command.h"
#include "common.h"

const byte START_BUTTON_PIN = 2;
int startSwitchState;
IntervalTimer startButtonDebounceTimer;

struct SequenceCommand {
  uint32_t startMs;
  Command command;
};

const int SEQUENCE_LENGTH = 13;
SequenceCommand sequence[] = { 
  { 00000, {NO_FLAG,NO_FLAG,3,0}},
  { 60000, {NO_FLAG,NO_FLAG,2,0}},
  { 90000, {NO_FLAG,NO_FLAG,1,3}},
  {120000, {NO_FLAG,NO_FLAG,1,0}},
  {150000, {NO_FLAG,NO_FLAG,0,3}},
  {160000, {NO_FLAG,NO_FLAG,0,2}},
  {170000, {NO_FLAG,NO_FLAG,0,1}},
  {175000, {NO_FLAG,NO_FLAG,0,1}},
  {176000, {NO_FLAG,NO_FLAG,0,1}},
  {177000, {NO_FLAG,NO_FLAG,0,1}},
  {178000, {NO_FLAG,NO_FLAG,0,1}},
  {179000, {NO_FLAG,NO_FLAG,0,1}},
  {180000, {NO_FLAG,NO_FLAG,1,0}},
};

int sequencePosition;
uint32_t startMs;

boolean sequenceRunning;

void setup() {
  DEBUG_SERIAL.begin(9600);
  CONTROL_SERIAL.begin(9600);
  delay(1000);

  startSwitchState = 2;
  sequenceRunning = false;

  setupStartButton();
  
  DEBUG_SERIAL.println("Setup Complete");
  
}


void loop() {
  if(sequenceRunning) {
    checkNextCommand();
  }
}

void setupStartButton() {
  
  pinMode(START_BUTTON_PIN , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN ), checkStartButton, CHANGE);
  checkStartButton();
}

void checkStartButton() {
  startSwitchState = digitalRead(START_BUTTON_PIN);
  startButtonDebounceTimer.begin(startButtonDebounce, DEBOUNCE_US);
}

void startButtonDebounce() {
  startButtonDebounceTimer.end();

  int newState = digitalRead(START_BUTTON_PIN );
  if(startSwitchState == newState) {
    if(startSwitchState == HIGH) {
      if(!sequenceRunning){
        startSequence();
      }
    }
  }

  noInterrupts();
  startSwitchState = newState;
  interrupts();
}

void startSequence() {
  DEBUG_SERIAL.println("starting sequence");
  sequencePosition = 0;
  sequenceRunning = true;
  startMs=millis();
}

void checkNextCommand() {

    uint32_t nowMs = millis()-startMs;

    //Check if we've reached the next point of the sequence
    if(sequence[sequencePosition].startMs < nowMs) {
      sendCommand(sequence[sequencePosition].command);
      sequencePosition+=1;
      if(sequencePosition < SEQUENCE_LENGTH) {
        DEBUG_SERIAL.printf("\tNext command at %d\n",sequence[sequencePosition].startMs);
      }
    }
  
    if(sequencePosition == SEQUENCE_LENGTH) {
      DEBUG_SERIAL.println("Sequence complete");
      sequenceRunning = false;
    }
}

