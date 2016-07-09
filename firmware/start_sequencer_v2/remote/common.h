#pragma once

#include "flag.h"

#define CONTROL_SERIAL Serial1
#define DEBUG_SERIAL Serial

const uint16_t DEBOUNCE_US = 10000;

const uint16_t LONG_HORN_MS = 750;
const uint16_t SHORT_HORN_MS = 250;
const uint8_t HORN_PIN = 13;

const uint8_t COMPRESSOR_PIN = 14;
const uint8_t PRESSURE_SWITCH = 2; //A0;

//Flag pins defined in flags.cpp
const uint8_t FLAG_COUNT = 2;
extern Flag flags[];
