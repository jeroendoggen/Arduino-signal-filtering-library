// Arduino Signal Filtering Library: fir filter example
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <iirFilter.h>

iirFilter Filter;

int value;
int filtered;

void setup()
{
  Serial.begin(9600);
  Filter.begin();
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
