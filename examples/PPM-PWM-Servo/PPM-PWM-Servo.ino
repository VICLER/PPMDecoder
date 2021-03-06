#include <PPM.h>
#include <Servo.h>

#define SERVO_PIN 9    // servo signal pin
#define CHANNELS 8    // max ppm channels
#define PPM_PIN 2    // receiver ppm pin
#define LED 5       // led pin

Servo servo;

void setup() {
  ppm.begin(PPM_PIN, CHANNELS);
  servo.attach(SERVO_PIN);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

void loop() {

  //servo.writeMicroseconds(ppm.getServo_us(1)); // write in range from (544 - 2400)us -> (0 - 180)deg. This is much faster than servo.write(0 - 180)
  servo.writeMicroseconds(ppm.get(1));          // write raw PPM value to servo (1000 - 2000)us
  analogWrite(LED, ppm.getPWM(3));             // write PWM value from channel 3 to led

}
