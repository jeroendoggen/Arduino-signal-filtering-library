// Arduino Signal Filtering Library
// Copyright 2012-2013 Jeroen Doggen (jeroendoggen@gmail.com)

#include <SignalFilter.h>

SignalFilter Filter;

int value;
int filtered;
unsigned long starttime,endtime,timedifference;

void setup()
{
  Serial.begin(115200);
  Filter.begin();
  Filter.setFilter('m');
  Filter.setOrder(2);
}

void loop()
{
  value = analogRead(A0);
  starttime=micros();
  filtered= Filter.run(value);
  endtime=micros();
  timedifference=endtime-starttime;
  // Serial.print("In: ");
  Serial.print(value);
  //Serial.print(" - Out: ");
  Serial.print(",");
  Serial.println(filtered);
  Serial.print(" - Time: ");
  Serial.println(timedifference);
  delay(100);                                     //make it readable
}
