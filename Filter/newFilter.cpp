// Arduino Signal Filtering Library
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <Arduino.h>
#include <newFilter.h>

/// Constructor
newFilter::newFilter()
{
}

/// Begin function: set default filter options
void newFilter::begin()
{
}

/// Just a placeholder
int newFilter::run(int data)
{
  return (data*2);                                // Filter just return the double of the input sample
}
