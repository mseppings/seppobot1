#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *frontLeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *frontRightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rearLeftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rearRightMotor = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void loop() {

  uint8_t i;
  i=100;

  //FORWARD
  setMotors(i, FORWARD, FORWARD, FORWARD, FORWARD);
  delay(2000);
  //RIGHT
  setMotors(i, FORWARD, BACKWARD, BACKWARD, FORWARD);
  delay(2000);
  //BACKWARDS
  setMotors(i, BACKWARD, BACKWARD, BACKWARD, BACKWARD);
  delay(2000);
  //LEFT
  setMotors(i, BACKWARD, FORWARD, FORWARD, BACKWARD);
  delay(2000);
  
}

void setMotors(uint8_t frontLeftDirecton, uint8_t frontLeftSpeed, 
               uint8_t frontRightDirecton, uint8_t frontRightSpeed, 
               uint8_t rearLeftDirecton, uint8_t rearLeftSpeed, 
               uint8_t rearRightDirecton, uint8_t rearRightSpeed) {

  frontLeftMotor->setSpeed(frontLeftSpeed);
  frontRightMotor->setSpeed(frontRightSpeed);
  rearLeftMotor->setSpeed(rearLeftSpeed);
  rearRightMotor->setSpeed(rearRightSpeed);

  frontLeftMotor->run(frontLeftDirecton);
  frontRightMotor->run(frontRightDirecton);
  rearLeftMotor->run(rearLeftDirecton);
  rearRightMotor->run(rearRightDirecton);

               }

void setMotors(uint8_t motorSpeed, uint8_t frontLeftDirecton, uint8_t frontRightDirecton,
               uint8_t rearLeftDirecton, uint8_t rearRightDirecton) {

  setMotors(frontLeftDirecton, motorSpeed, 
               frontRightDirecton, motorSpeed, 
               rearLeftDirecton, motorSpeed, 
               rearRightDirecton, motorSpeed);

               }
