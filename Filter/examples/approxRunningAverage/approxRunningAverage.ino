// Arduino Signal Filtering Library: approx. running average example
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <approxRunningAverage.h>

approxRunningAverage Filter;

int value;
int filtered;

int order = 8;

void setup()
{
  Serial.begin(9600);
  Filter.begin(order);
}

void loop()
{
  value = analogRead(A0);
  filtered= Filter.run(value);
  Serial.print("In: ");
  Serial.print(value);
  Serial.print(" - Out: ");
  Serial.println(filtered);
  delay(500);                                     //make it readable
}
