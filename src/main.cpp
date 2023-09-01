#include <Arduino.h>
#include <assert.h>

#include "../lib/board_data/board_pins.hpp"
#include "../lib/motor/motor.hpp"
#include "../lib/gyro/gyro.hpp"

#define DRIVER1_TEST
#define DRIVER2_TEST
//#define BMX_TEST

#ifdef DRIVER1_TEST
DRIVER md1(DRIVER2_pin);
MOTOR motor1(MOTOR1_pin,1.0f);
MOTOR motor2(MOTOR2_pin,1.0f);
#endif //DRIVER1_TEST

#ifdef DRIVER2_TEST
DRIVER md2(DRIVER1_pin);
MOTOR motor3(MOTOR3_pin,1.0f);
MOTOR motor4(MOTOR4_pin,1.0f);
#endif //DRIVER2_TEST

BMX055 gyro_sens(Wire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.printf("acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z,mag_x,mag_y,mag_z\r\n");
  Wire.begin();

#ifdef DRIVER1_TEST
  md1.init();
  motor1.init();
  motor2.init();
#endif //DRIVER1_TEST
#ifdef DRIVER1_TEST
  md2.init();
  motor3.init();
  motor4.init();
#endif //DRIVER1_TEST
  gyro_sens.init();
}

void loop() {
  // put your main code here, to run repeatedly:
#ifdef DRIVER1_TEST
  motor1.out(1);
  motor2.out(1);
  delay(1000);
  motor1.out(0);
  motor2.out(0);
  delay(1000);
  motor1.out(-1); 
  motor2.out(-1); 
  delay(1000);
  motor1.free();
  motor2.free();
  delay(1000);
  Serial.printf("loop done\n");
#endif //DRIVER1_TEST
#ifdef DRIVER2_TEST
  motor3.out(1);
  motor4.out(1);
  delay(1000);
  motor3.out(0);
  motor4.out(0);
  delay(1000);
  motor3.out(-1); 
  motor4.out(-1); 
  delay(1000);
  motor3.free();
  motor4.free();
  delay(1000);
  Serial.printf("loop done\n");
#endif //DRIVER1_TEST

#ifdef BMX_TEST
  xyz_t data = gyro_sens.read_acc();
  Serial.printf("%f,%f,%f,",data.x,data.y,data.z);
  data = gyro_sens.read_gyro();
  Serial.printf("%f,%f,%f,",data.x,data.y,data.z);
  data = gyro_sens.read_mag();
  Serial.printf("%f,%f,%f\r\n",data.x,data.y,data.z);
  delay(50);
#endif //BMX_TEST
}