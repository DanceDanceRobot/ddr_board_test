#include <Arduino.h>
#include <assert.h>

typedef struct{
  uint8_t pin;
  uint8_t ch;
}pwm_t;

typedef struct{
  pwm_t pwm1;
  pwm_t pwm2;
}mpwm_t;

typedef struct{
  mpwm_t motor1;
  mpwm_t motor2;
  uint8_t ERR;
  uint8_t MODE;
  uint8_t STBY;
} md_pin_t;

const pwm_t pwm_a1 = {32,0};
const pwm_t pwm_a2 = {25,1};
const pwm_t pwm_b1 = {33,2};
const pwm_t pwm_b2 = {26,3};

const mpwm_t mpwm1 = {pwm_a1,pwm_a2};
const mpwm_t mpwm2 = {pwm_b1,pwm_b2};
const md_pin_t md1 = {mpwm1,mpwm2,27,14,12};

enum class MD_MODE{
  IN,
  PHASE,
};

void MD_init(md_pin_t md,MD_MODE mode);
void motor_turn(mpwm_t pin,float duty);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.printf("start\r\n");
  MD_init(md1,MD_MODE::PHASE);
}

void loop() {
  // put your main code here, to run repeatedly:
  motor_turn(mpwm1,1);
  delay(1000);
  motor_turn(mpwm1,0);
  delay(1000);
  motor_turn(mpwm1,-1);
  delay(1000);
  motor_turn(mpwm1,0);
  delay(1000);
}

void MD_init(md_pin_t md,MD_MODE mode){
  //GPIO init
  pinMode(md.MODE, OUTPUT);
  pinMode(md.STBY, OUTPUT);
  pinMode(md.ERR, INPUT);

  //PWM init
  ledcSetup(md.motor1.pwm1.ch,78125,10); 
  ledcAttachPin(md.motor1.pwm1.pin, md.motor1.pwm1.ch);
  ledcSetup(md.motor1.pwm2.ch,78125,10); 
  ledcAttachPin(md.motor1.pwm2.pin,md.motor1.pwm2.ch);

  ledcSetup(md.motor2.pwm1.ch,78125,10); 
  ledcAttachPin(md.motor2.pwm1.pin, md.motor2.pwm1.ch);
  ledcSetup(md.motor2.pwm2.ch,78125,10); 
  ledcAttachPin(md.motor2.pwm2.pin,md.motor2.pwm2.ch);

  //set
  switch(mode){
    case MD_MODE::IN:
      digitalWrite(md.MODE,LOW);
      break;
    case MD_MODE::PHASE:
      digitalWrite(md.MODE,HIGH);
      break;
  }
  digitalWrite(md.STBY,HIGH);
}

void motor_turn(mpwm_t pin,float duty){
  assert(duty<1 || duty>-1);
  ledcWrite(pin.pwm2.ch,(duty+1)*512);
  ledcWrite(pin.pwm1.ch,1024);
}