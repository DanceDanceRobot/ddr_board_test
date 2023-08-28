#include <Arduino.h>
#include <assert.h>

#include "board_pins.hpp"
#include "motor.hpp"

DRIVER md1(DRIVER1_pin);

MOTOR motor1(MOTOR1_pin,1.0f);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.printf("start\r\n");

  md1.init();
  motor1.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.out(1);
  delay(1000);
  motor1.free();
  delay(1000);
  motor1.out(-1); 
  delay(1000);
  motor1.free();
  delay(1000);
}