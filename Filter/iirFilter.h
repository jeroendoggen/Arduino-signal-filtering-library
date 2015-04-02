// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#ifndef iirFilter_h
#define iirFilter_h
#include <Arduino.h>
#include <Filter.h>

class iirFilter : public Filter
{
  public:
    iirFilter();
    void begin();

    int run(int data);

  private:
    int _x[3];
    int _y[3];
};
#endif
