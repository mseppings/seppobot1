#include <Adafruit_MotorShield.h>
#include <IRremote.h> // include the IRremote library

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *frontLeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *frontRightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *rearLeftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rearRightMotor = AFMS.getMotor(4);

//IRREMOTE STUFF
#define RECEIVER_PIN 2 // define the IR receiver pin
IRrecv receiver(RECEIVER_PIN); // create a receiver object of the IRrecv class
decode_results results; // create a results object of the decode_results class
unsigned long key_value = 0; // variable to store the key value

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  Serial.begin(9600); // begin serial communication with a baud rate of 9600
  receiver.enableIRIn(); // enable the receiver
  receiver.blink13(true); // enable blinking of the built-in LED when an IR signal is received
  
}

void loop() {

  uint8_t motorSpeed;
  motorSpeed=100;

  if (receiver.decode(&results)) { // decode the received signal and store it in results
    if (results.value == 0xFFFFFFFF) { // if the value is equal to 0xFFFFFFFF
      results.value = key_value; // set the value to the key value
    }
    switch (results.value) { // compare the value to the following cases
      case 0xFD00FF: // if the value is equal to 0xFD00FF
        Serial.println("VOL-"); // print "POWER" in the Serial Monitor
        if((motorSpeed-10)<255){
          motorSpeed=motorSpeed+10;
          Serial.print("Motor speed set to ");
          Serial.println(motorSpeed);
        }
        break;
      case 0xFD807F:
        Serial.println(">||");
        break;
      case 0xFD40BF:
        Serial.println("VOL+");
        if((motorSpeed-10)<0){
          motorSpeed=motorSpeed-10;
          Serial.print("Motor speed set to ");
          Serial.println(motorSpeed);
        }
        break;
      case 0xFD20DF:
        Serial.println("SETUP");
        moveForwardLeft(motorSpeed);
        break;
      case 0xFDA05F:
        Serial.println("^");
        moveForward(motorSpeed);
        break ;
      case 0xFD609F:
        Serial.println("STOP/MODE");
        moveForwardRight(motorSpeed);
        break ;
      case 0xFD10EF:
        Serial.println("<");
        moveLeft(motorSpeed);
        break ;
      case 0xFD906F:
        Serial.println("ENTER/SAVE");
        moveStop();       
        break ;
      case 0xFD50AF:
        Serial.println(">");
        moveRight(motorSpeed);
        break ;
      case 0xFD30CF:
        Serial.println("0 10+");
        moveBackwardLeft(motorSpeed);
        break ;
      case 0xFDB04F:
        Serial.println("\\/");
        moveBackward(motorSpeed);
        break ;
      case 0xFD708F:
        Serial.println("<-");
        moveBackwardRight(motorSpeed);
        break ;
      case 0xFD08F7:
        Serial.println("1");
        break ;
      case 0xFD8877:
        Serial.println("2");
        break ;
      case 0xFD48B7:
        Serial.println("3");
        break ;
      case 0xFD28D7:
        Serial.println("4");
        break ;
      case 0xFDA857:
        Serial.println("5");
        break ;
      case 0xFD6897:
        Serial.println("6");
        break ;
      case 0xFD18E7:
        Serial.println("7");
        break ;
      case 0xFD9867:
        Serial.println("8");
        break ;
      case 0xFD58A7:
        Serial.println("9");
        break ;
    }
    key_value = results.value; // store the value as key_value
    receiver.resume(); // reset the receiver for the next code
  }
  
  
  
  
  
  
  
  
  //TEST MOVEMENTS
  
  uint8_t i;
  i=100;

  //CIRCLISH!
  /*moveForward(i);
  delay(1000);
  moveForwardRight(i);
  delay(1000);
  moveRight(i);
  delay(1000);
  moveBackwardRight(i);
  delay(1000);
  moveBackward(i);
  delay(1000);
  moveBackwardLeft(i);
  delay(1000);
  moveLeft(i);
  delay(1000);
  moveForwardLeft(i);
  delay(1000);
  */

  // ZIGZAG FORWARD
  /*
  moveForwardRight(i);
  delay(2000);
  moveForwardLeft(i);
  delay(2000);
  */
  
  /*ROTATIONTEST
   * rotateClockwiseAroundCenter(i);
  delay(2500);
  rotateAnticlockwiseAroundCenter(i);
  delay(2500);

  rotateClockwiseAroundBackCenter(i);
  delay(2500);
  rotateAnticlockwiseAroundBackCenter(i);
  delay(2500);

  rotateClockwiseAroundFrontCenter(i);
  delay(2500);
  rotateAnticlockwiseAroundFrontCenter(i);
  delay(2500);
  */

  /*moveForward(i);
  delay(2000);
  moveRight(i);
  delay(2000);
  moveBackward(i);
  delay(2000);
  moveLeft(i);
  delay(2000);
  */
}

// Rotation
void rotateClockwiseAroundCenter(uint8_t motorSpeed){
  setMotors(motorSpeed, FORWARD, BACKWARD, FORWARD, BACKWARD);
}
void rotateAnticlockwiseAroundCenter(uint8_t motorSpeed){
  setMotors(motorSpeed, BACKWARD, FORWARD, BACKWARD, FORWARD);
}
void rotateClockwiseAroundBackCenter(uint8_t motorSpeed){
  setMotors(motorSpeed, FORWARD, BACKWARD, RELEASE, RELEASE);
}
void rotateAnticlockwiseAroundBackCenter(uint8_t motorSpeed){
  setMotors(motorSpeed, BACKWARD, FORWARD, RELEASE, RELEASE);
}
void rotateClockwiseAroundFrontCenter(uint8_t motorSpeed){
  setMotors(motorSpeed, RELEASE, RELEASE, BACKWARD, FORWARD);
}
void rotateAnticlockwiseAroundFrontCenter(uint8_t motorSpeed){
  setMotors(motorSpeed, RELEASE, RELEASE, FORWARD, BACKWARD);
}


// Compass Points
void moveForward(uint8_t motorSpeed) {
  setMotors(motorSpeed, FORWARD, FORWARD, FORWARD, FORWARD);
}
void moveForwardRight(uint8_t motorSpeed) {
  setMotors(motorSpeed, FORWARD, RELEASE, RELEASE, FORWARD);
}
void moveForwardLeft(uint8_t motorSpeed) {
  setMotors(motorSpeed, RELEASE, FORWARD, FORWARD, RELEASE);
}
void moveBackward(uint8_t motorSpeed) {
  setMotors(motorSpeed, BACKWARD, BACKWARD, BACKWARD, BACKWARD);
}
void moveBackwardLeft(uint8_t motorSpeed) {
  setMotors(motorSpeed, BACKWARD, RELEASE, RELEASE, BACKWARD);
}
void moveBackwardRight(uint8_t motorSpeed) {
  setMotors(motorSpeed, RELEASE, BACKWARD, BACKWARD, RELEASE);
}
void moveRight(uint8_t motorSpeed) {
  setMotors(motorSpeed, FORWARD, BACKWARD, BACKWARD, FORWARD);
}
void moveLeft(uint8_t motorSpeed) {
  setMotors(motorSpeed, BACKWARD, FORWARD, FORWARD, BACKWARD);
}
void moveStop() {
  setMotors(0, RELEASE, RELEASE, RELEASE, RELEASE);
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
