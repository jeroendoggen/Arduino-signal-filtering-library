// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#ifndef firFilter_h
#define firFilter_h
#include <Arduino.h>
#include <Filter.h>

//#define ORDER 4
#define ORDER 8
//#define ORDER 16
//#define ORDER 32
//#define ORDER 64
//#define ORDER 128
//#define ORDER 256

class approxRunningAverage : public Filter
{
  public:
    approxRunningAverage();
    void begin(int order);
    
    int run(int sample);
    void printSamples();
  private:
    int _samples[ORDER];  // TODO: use malloc() and make it dynamic (vs .ino file)
    int _index;
    int _average;
    int _sum;
    byte _shift;
    byte _order;
};
#endif
