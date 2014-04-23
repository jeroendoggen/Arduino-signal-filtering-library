// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

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
