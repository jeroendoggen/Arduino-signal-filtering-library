// iirFilter.cpp - Arduino library to Filter Sensor Data with FIR filters
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)
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
