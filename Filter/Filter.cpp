// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com))

#include <Arduino.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include <pins_arduino.h>
#endif

#include <Filter.h>

/// Constructor
Filter::Filter()
{
  _x[0]=0;
  _x[1]=0;
  _x[2]=0;
  _average=0;
}

/// printSamples: Print out some samples (for debugging)
void Filter::printSamples()
{
  Serial.print(" ");
  Serial.print(_x[2]);

  Serial.print(" ");
  Serial.print(_x[1]);

  Serial.print(" ");
  Serial.print(_x[0]);
  Serial.print(" - ");
}
