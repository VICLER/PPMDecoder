#include <PPM.h>

#define CHANNELS 8   // max ppm channels
#define PPM_PIN 2   // receiver ppm pin


void setup() {
  ppm.begin(PPM_PIN, CHANNELS);
  Serial.begin(115200);
}

void loop() {
  
  for (uint8_t i = 1; i <= CHANNELS; i++) // print all channel values
  {
    Serial.print(ppm.get(i));
    Serial.print('\t');
  }
  Serial.println();
  delay(10);
  
}
