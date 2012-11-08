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
#include <SignalFilter.h>

/// Constructor
SignalFilter::SignalFilter()
{
}

/// Begin function: set default filter options
void SignalFilter::begin()
{
  setFilter('c');
  setOrder(1);
  _v[0]=0;
  _v[1]=0;
  _v[2]=0;
  _v[3]=0;
}

/// setFilter(char filter): Select filter: 'c' -> Chebyshev, 'b' -> Bessel
void SignalFilter::setFilter(char filter)
{
  _filter=filter;
}

/// selectOrder(int order): Select filter order (1 or 2)
void SignalFilter::setOrder(int order)
{
  _order=order;
}

/// filter: Runs the actual filter: input=rawdata, output=filtered data
int SignalFilter::run(int data)
{
// 	Uncomment for debugging
// 	Serial.println(_filter);
//	Serial.println(_order);
/// Chebyshev filters
  if(_filter=='c')                                
  {
    if(_order==1)                                 //ripple -3dB
    {
      _v[0] = _v[1];
      long tmp = ((((data * 3269048L) >>  2)      //= (3.897009118e-1 * data)
        + ((_v[0] * 3701023L) >> 3)               //+(  0.2205981765*v[0])
        )+1048576) >> 21;                         // round and downshift fixed point /2097152
      _v[1]= (short)tmp;
      return (short)(_v[0] + _v[1]);              // 2^
    }
    if(_order==2)                                 //ripple -1dB
    {
      _v[0] = _v[1];
      _v[1] = _v[2];
      long tmp = ((((data * 662828L) >>  4)       //= (    7.901529699e-2 * x)
        + ((_v[0] * -540791L) >> 1)               //+( -0.5157387562*v[0])
        + (_v[1] * 628977L)                       //+(  1.1996775682*v[1])
        )+262144) >> 19;                          // round and downshift fixed point /524288

      _v[2]= (short)tmp;
      return (short)((
        (_v[0] + _v[2])
        +2 * _v[1]));                             // 2^
    }
  }

/// Bessel filters
  if(_filter=='b')                                // Bessel filters
  {
    if(_order==1)                                 //Alpha Low 0.1
    {
      _v[0] = _v[1];
      long tmp = ((((data * 2057199L) >>  3)        //= (    2.452372753e-1 * x)
        + ((_v[0] * 1068552L) >> 1)                 //+(  0.5095254495*v[0])
        )+524288) >> 20;                            // round and downshift fixed point /1048576
      _v[1]= (short)tmp;
      return (short)(((_v[0] + _v[1])));            // 2^
    }
    if(_order==2)                                   //Alpha Low 0.1
    {
      _v[0] = _v[1];
      _v[1] = _v[2];
      long tmp = ((((data * 759505L) >>  4)         //= (    9.053999670e-2 * x)
        + ((_v[0] * -1011418L) >> 3)                //+( -0.2411407388*v[0])
        + ((_v[1] * 921678L) >> 1)                  //+(  0.8789807520*v[1])
        )+262144) >> 19;                            // round and downshift fixed point /524288

      _v[2]= (short)tmp;
      return (short)(((_v[0] + _v[2])+2 * _v[1]));  // 2^
    }
  }
  
/// Median filters
    if(_filter=='m')  // New filters
    {
     // Note: 
     //  quick & dirty dumb implementation that only keeps 3 samples: probably better to do insertion sort when more samples are needed in the calculation
     //   or Partial sort: http://en.cppreference.com/w/cpp/algorithm/nth_element
    if(_order==2)                                  
    {
      _v[0] = _v[1];
      _v[1] = _v[2];
      _v[2]= data;
      
      if (_v[2] < _v[1])
      {
        if (_v[2] < _v[0])
        {
          if (_v[1] < _v[0])
          {
            _median = _v[1];
          }
          else
          {
            _median = _v[0];
          } 
        }
        else
        {
          _median = _v[2]; 
        }
      }
      else
      {
        if (_v[2] < _v[0])
        {
            _median = _v[2];
        }
        else
        {
          if (_v[1] < _v[0])
          {
            _median = _v[0];
          }
          else
          {
            _median = _v[1];
          }
        }
      }
//    Serial.print(" ");
//    Serial.print(_v[2]);
//     
//    Serial.print(" ");
//    Serial.print(_v[1]);
//     
//    Serial.print(" ");
//    Serial.print(_v[0]);
//     
//    Serial.print(" Median:");
//    Serial.println(_median);
//     return (_median);
    }
    }
   
}

