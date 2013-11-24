// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

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
