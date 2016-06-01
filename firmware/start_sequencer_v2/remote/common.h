#pragma once

#include "flag.h"

#define CONTROL_SERIAL Serial1
#define DEBUG_SERIAL Serial

const long DEBOUNCE_US = 10000;

const long LONG_HORN_MS = 750;
const long SHORT_HORN_MS = 250;
const byte HORN_PIN = 13;

const byte COMPRESSOR_PIN = 14;
const byte PRESSURE_SWITCH = 2;

//Flag pins defined in flags.cpp
const byte FLAG_COUNT = 2;
extern Flag flags[];
