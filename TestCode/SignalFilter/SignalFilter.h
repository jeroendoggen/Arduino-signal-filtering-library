// Filter.h - Arduino library to Filter Sensor Data
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)
//   Chebyshev & Bessel filter code and parameters by Jurgen Schwietering
//   http://www.schwietering.com/jayduino/filtuino
//
// Version History:
//  Version 0.1: Low pass filters: chebyshev, bessel (1st & 2nd order)
//  Version 0.2: Median filter
// Roadmap
//  Version 0.3: Variable Length Running Average
//  Version 0.4: Kalman Filter
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

#ifndef SignalFilter_h
#define SignalFilter_h
#include <Arduino.h>

class SignalFilter
{
  public:
    SignalFilter();
    void begin();

    void setFilter(char filter);                  //'c' -> Chebyshev, 'b' -> Bessel
    void setOrder(int order);                     // only 1 or 2
    void printSamples();

    int run(int data);

  private:

    int runChebyshev(int data);
    int runBessel(int data);
    int runMedian(int data);
    int runGrowing(int data);
    int runGrowing2(int data);
    char _filter;
    int _order;
    int _average;
    int _median;
    int _helper;
    int _counter;

    int _v[3];
};
#endif
