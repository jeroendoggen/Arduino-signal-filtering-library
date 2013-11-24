// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

#include <SignalFilter.h>

SignalFilter Filter;

int value;
int filtered;

void setup()
{
  Serial.begin(9600);
  Filter.begin();
  Filter.setFilter('m');
  Filter.setOrder(2);
}

void loop()
{
  value = analogRead(A0);
  filtered= Filter.run(value);
  Serial.print("In: ");
  Serial.print(value);
  Serial.print(" - Out: ");
  Serial.println(filtered);
  delay(100);                                     //make it readable
}
