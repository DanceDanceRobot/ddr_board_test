#include <Arduino.h>
#include <assert.h>

#include "../lib/board_data/board_pins.hpp"
#include "../lib/motor/motor.hpp"
#include "../lib/gyro/gyro.hpp"

#define MOTOR_TEST
//#define BMX_TEST

DRIVER md1(DRIVER1_pin);
MOTOR motor1(MOTOR1_pin,1.0f);

BMX055 gyro_sens(Wire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.printf("acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z,mag_x,mag_y,mag_z\r\n");
  Wire.begin();

  md1.init();
  motor1.init();
  gyro_sens.init();
}

void loop() {
  // put your main code here, to run repeatedly:
#ifdef MOTOR_TEST
  motor1.out(1);
  delay(1000);
  motor1.free();
  delay(1000);
  motor1.out(-1); 
  delay(1000);
  motor1.free();
  delay(1000);
#endif //MOTOR_TEST

#ifdef BMX_TEST
  xyz_t data = gyro_sens.acc();
  Serial.printf("%f,%f,%f,",data.x,data.y,data.z);
  data = gyro_sens.gyro();
  Serial.printf("%f,%f,%f,",data.x,data.y,data.z);
  data = gyro_sens.mag();
  Serial.printf("%f,%f,%f\r\n",data.x,data.y,data.z);
  delay(50);
#endif //BMX_TEST
}