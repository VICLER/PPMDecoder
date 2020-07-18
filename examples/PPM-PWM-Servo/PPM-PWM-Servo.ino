#include <PPM.h>
#include <Servo.h>

#define LED 5            // led pin
#define PPM_PIN 2       // receiver ppm pin
#define CHANNELS 8     // max ppm channels
#define SERVO_PIN 9   // servo signal pin

Servo servo;

void setup() {
  ppm.begin(PPM_PIN, CHANNELS);
  pinMode(LED, OUTPUT);
  servo.attach(SERVO_PIN);
  Serial.begin(115200);
}

void loop() {
  for (uint8_t i = 1; i <= CHANNELS; i++) { // list all channel values beginning from 1
    Serial.print(ppm.get(i));
    Serial.print('\t');
  }
  Serial.println();
  delay(10);

  //servo.writeMicroseconds(ppm.getServo_us(1)); // write in range from (544 - 2400)us. That is from 0 to 180 degrees. This is much faster than servo.write(0 - 180)
  servo.writeMicroseconds(ppm.get(1));          // write raw PPM value to servo (1000 - 2000)us
  analogWrite(LED, ppm.getPWM(3));             // write PWM value from channel 3 to led
}
