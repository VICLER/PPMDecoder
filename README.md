![PROJECT_PHOTO](https://github.com/VICLER/PPMDecoder/blob/master/ppm_img.PNG)
# PPMDecoder
 Arduino library for decoding PPM receiver signal

## Features
- Small size and easy to use
- Non-Blocking operation using interrupts
- Precise resolution of signal measuring (+- 0.5us)
- Fast PPM to PWM (0-255) and Servo (544-2400us) conversion
- Compatible with all ATMega328 16Mhz or 8Mhz Arduino boards

## How to use
```C++
#include<PPM.h>                        // include library
```
```C++
ppm.begin(PPM_PIN, MAX_CHANNELS);     // init in void setup() // works only with pin 2(PD2) or pin 3(PD3)
```
```C++
ppm.available();                     // returns 0 if there is no valid pulses from receiver
```
```C++
ppm.get(CHANNEL_NUMBER);            // get channel value in us
```
```C++
ppm.getPWM(CHANNEL_NUMBER);        // get pwm (0-255) channel value
```
```C++
ppm.getServo_us(CHANNEL_NUMBER);  // get Servo value (0-180)deg for using with Servo.writeMicroseconds() in range (544-2400)us
```
## Example
```C++
#include <PPM.h>

#define PPM_PIN 2       // receiver ppm pin
#define CHANNELS 8     // max ppm channels

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
```