// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <Arduino.h>
#include <medianFilter.h>

/// Constructor
medianFilter::medianFilter()
{
  _x[0]=0;
  _x[1]=0;
  _x[2]=0;
  _median=0;
}

/// Begin function: set default filter options
void medianFilter::begin()
{
}

/// Just a placeholder
int medianFilter::run(int data)
{
  // Note:
  //  quick & dirty dumb implementation that only keeps 3 samples: probably better to do insertion sort when more samples are needed in the calculation
  //   or Partial sort: http://en.cppreference.com/w/cpp/algorithm/nth_element
  // On better inspection of this code... performance seem quite good (more info in the commented out code below)
  // TODO: compare with: http://embeddedgurus.com/stack-overflow/tag/median-filter/
  _x[0] = _x[1];
  _x[1] = _x[2];
  _x[2]= data;

  // printSamples();

  if (_x[2] < _x[1]) {
    if (_x[2] < _x[0]) {
      if (_x[1] < _x[0]) {
        _median = _x[1];
      }
      else {
        _median = _x[0];
      }
    }
    else {
      _median = _x[2];
    }
  }
  else {
    if (_x[2] < _x[0]) {
      _median = _x[2];
    }
    else {
      if (_x[1] < _x[0]) {
        _median = _x[0];
      }
      else {
        _median = _x[1];
      }
    }
  }
  return (_median);
}


// Median filter (148 bytes, 12 microseconds)
// less efficient, but more readable?
//   int medianFilter::run(int data)
//   {
//     _x[0] = _x[1];
//     _x[1] = _x[2];
//     _x[2]= data ;
//
// //printSamples();
//
//     if( ((_x[2] < _x[1]) && (_x[2] > _x[0])) ||(( _x[2] < _x[0]) && (_x[2] > _x[1])))
//       return (_x[2]);
//
//     if( (_x[1] < _x[2] && _x[1] > _x[0]) ||( _x[1] < _x[0] && _x[1] > _x[2]))
//       return (_x[1]);
//
//     if( (_x[0] < _x[2] && _x[0] > _x[1]) ||( _x[0] < _x[1] && _x[0] > _x[2]))
//       return (_x[0]);
//   }

// Median filter (78 bytes, 12 microseconds)
// based on: http://embeddedgurus.com/stack-overflow/tag/median-filter/
// same code size as my median filter code

//   int medianFilter::run(int data)
//   {
//     _x[0] = _x[1];
//     _x[1] = _x[2];
//     _x[2]= data ;
//
//     int middle;
//
//     if ((_x[0] <= _x[1]) && (_x[0] <= _x[2]))
//     {
//       middle = (_x[1] <= _x[2]) ? _x[1] : _x[2];
//     }
//     else if ((_x[1] <= _x[0]) && (_x[1] <= _x[2]))
//     {
//       middle = (_x[0] <= _x[2]) ? _x[0] : _x[2];
//     }
//     else
//     {
//       middle = (_x[0] <= _x[1]) ? _x[0] : _x[1];
//     }
//     return middle;
//   }

/// printSamples: Print out some samples (for debugging)
void medianFilter::printSamples()
{
  Serial.print(" ");
  Serial.print(_x[2]);

  Serial.print(" ");
  Serial.print(_x[1]);

  Serial.print(" ");
  Serial.print(_x[0]);
  Serial.print(" - ");
}


