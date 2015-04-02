// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <Arduino.h>
#include <iirFilter.h>

/// Constructor
iirFilter::iirFilter()
{
  _y[0]=0;
  _y[1]=0;
  _y[2]=0;
}

/// Begin function: set default filter options
void iirFilter::begin()
{
}

int iirFilter::run(int data)
{
// not an iirFilter implementation (just a placeholder)
  _x[0] = _x[1];
  long tmp = ((((data * 3269048L) >>  2)          //= (3.897009118e-1 * data)
    + ((_x[0] * 3701023L) >> 3)                   //+(  0.2205981765*v[0])
    )+1048576) >> 21;                             // round and downshift fixed point /2097152
  _x[1]= (int)tmp;
  return (int)(_x[0] + _x[1]);                    // 2^
}
