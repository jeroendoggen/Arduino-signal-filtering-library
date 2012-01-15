#include <Filter.h>

Filter filt;

int value;
int filtered;

void setup()
{
  Serial.begin(9600);
  filt.begin();
  filt.setFilter('c');
  filt.setOrder(1);
}

void loop()
{
  value = analogRead(A0);
  filtered= filt.filter(value);
  Serial.print("In: ");
  Serial.print(value);  
  Serial.print(" - Out: ");
  Serial.println(filtered);  
  delay(500); //make it readable
} 
