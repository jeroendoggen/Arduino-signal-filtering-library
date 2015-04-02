// Arduino Signal Filtering Library: newFilter example
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <newFilter.h>

newFilter Filter;

int value;
int filtered;

void setup()
{
  Serial.begin(115200);
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
