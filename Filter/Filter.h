// Filter.h - Arduino library to Filter Sensor Data
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)
//
// Version History:
//  Version 0.1:
// Roadmap
//  Version 0.2: ?
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

#ifndef Filter_h
#define Filter_h

#define __cxa_pure_virtual()

//abstract class Filter
class Filter
{
  public:
    Filter();

  protected:
    int _average;
    int _x[3];

  private:
    virtual int run(int data)=0;
    void printSamples();
};
#endif
