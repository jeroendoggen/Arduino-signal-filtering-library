// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <Arduino.h>
#include <approxRunningAverage.h>

/// Constructor
approxRunningAverage::approxRunningAverage()
{
}

/// Begin function: set default filter options
void approxRunningAverage::begin(int order)
{
  _sum = 0;
  _index=0;
  _average=0;
  _order=order;
  for(byte i=0;i++;i<_order)
  {
    _samples[i]=0;
  }
  switch (_order) {
    case 4:
      _shift = 2;
      break;
    case 8:
      _shift = 3;
      break;
    case 16:
      _shift = 4;
      break;
    case 32:
      _shift = 5;
      break;
    case 64:
      _shift = 6;
      break;
    case 128:
      _shift = 7;
      break;
    case 256:
      _shift = 8;
      break;
  }
}

/// Calculate the average without saving the previous 'order' values
int approxRunningAverage::run(int sample)
{
  _sum = _sum - _average;             // remove the average from the sum -> 'similar' to removing the oldest sample
  _sum = _sum + sample;               // add new sample to the running sum
  _average = _sum >> _shift;          // calculate the new running average
  return (_average);                  // return the new running average
}

/// printSamples: Print out some samples (for debugging)
// TODO: remove this from parent class?
void approxRunningAverage::printSamples()
{
}
