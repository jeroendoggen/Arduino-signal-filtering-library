// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#ifndef Filter_h
#define Filter_h

#define __cxa_pure_virtual()

//abstract class Filter
class Filter
{
  public:
    Filter();

    virtual int run(int data)=0;
    virtual void printSamples()=0;
};
#endif
