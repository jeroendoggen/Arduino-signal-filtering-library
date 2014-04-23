// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

#ifndef MedianFilter_h
#define MedianFilter_h
#include <Arduino.h>
#include <Filter.h>

class MedianFilter : public Filter
{
  public:
    MedianFilter();
    void begin();

    int run(int data);

  private:
    int _x[3];
    int _median;
};
#endif
