// Arduino Signal Filtering Library: fixedSamplingRate.ino
// Copyright 2012-2015 Jeroen Doggen (jeroendoggen@gmail.com)

#include <firFilter.h>
#include <TimerOne.h>  // https://github.com/PaulStoffregen/TimerOne/

firFilter Filter;

volatile int newSample;
boolean sampled = false;
int filtered;

void getSample()
{
  newSample = analogRead(A0);
  sampled = true;
}

void setup()
{
  Serial.begin(115200);
  Filter.begin();
  // Set period to 1000 ms --> TODO: is this exact (@16 Mhz: 16000 x 0.0625 uS = 1000 ms... not 100% sure if correct!)
  // check here: https://github.com/PaulStoffregen/TimerOne/blob/master/TimerOne.h#L179
  Timer1.initialize(1000);
  Timer1.attachInterrupt(getSample); // getSample to run every 1000 ms
}

void loop()
{
  if(sampled)
  {
    filtered = Filter.run(newSample);
    Filter.printSamples();
  }
}
