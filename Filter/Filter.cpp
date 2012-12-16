// Filter.h - Arduino library to Filter Sensor Data
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)
// For more information: variable declaration, changelog,... see Filter.h
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

/// SignalFilter - Library to Filter Sensor Data using digital filters
/// Available filters: Chebyshev & Bessel low pass filter (1st & 2nd order)

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
