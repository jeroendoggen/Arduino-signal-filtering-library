// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#ifndef medianFilter_h
#define medianFilter_h
#include <Arduino.h>
#include <Filter.h>

class medianFilter : public Filter
{
  public:
    medianFilter();
    void begin();

    int run(int data);
    void printSamples();

  private:
    int _x[3];
    int _median;
};
#endif
