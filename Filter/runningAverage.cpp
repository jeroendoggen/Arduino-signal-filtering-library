// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <Arduino.h>
#include <runningAverage.h>

/// Constructor
runningAverage::runningAverage()
{
}

/// Begin function: set default filter options
void runningAverage::begin(int order)
{
  _sum = 0;
  _index=0;
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

/// Calculate the average while saving the previous 'order' values
int runningAverage::run(int sample)
{
  _sum = _sum - _samples[_index];     // remove oldest sample from running sum
  _samples[_index] = sample;          // add new sample to the buffer
  _sum = _sum + sample;               // add new sample to the running sum
  
  _index++;                           // change the index to the next location
  if(_index == _order) _index = 0;    // move the index to the first location
  
  return (_sum >> _shift);            // calculate & return the new running average
}

/// printSamples: Print out some samples (for debugging)
// TODO: remove this from parent class?
void runningAverage::printSamples()
{
}
