// firFilter.h - Arduino library to Filter Sensor Data
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

#ifndef firFilter_h
#define firFilter_h
#include <Arduino.h>
#include <Filter.h>

class firFilter : public Filter
{
  public:
    firFilter();
    void begin();

    int run(int data);

  private:
};
#endif
