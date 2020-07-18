![PROJECT_PHOTO](https://github.com/VICLER/PPMDecoder/blob/master/ppm_img.PNG)
# PPMDecoder
 Arduino library for decoding PPM receiver signal

## Features
- Small size and simple to use
- Non-Blocking operation using interrupts
- Precise resolution of signal measuring (+- 0.5us)
- Fast PPM to PWM (0-255) and Servo (544-2400us) conversion
- Compatible with all ATMega328 16Mhz or 8Mhz Arduino boards

## How to use
```C++
#include<PPM.h>                        // include library
ppm.begin(PPM_PIN, MAX_CHANNELS);     // init in void setup() // works only with pin 2(PD2) or pin 3(PD3)
ppm.available();                     // returns 0 if there is no valid pulses from receiver
ppm.get(CHANNEL_NUMBER);            // get channel value in us 
ppm.getPWM(CHANNEL_NUMBER);        // get pwm (0-255) channel value
ppm.getServo_us(CHANNEL_NUMBER);  // get Servo value (0-180)deg for using with Servo.writeMicroseconds() in range (544-2400)us
```