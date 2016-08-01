/*
Aigamo-robot program
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


//Create the motor shield object
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);
  Serial.println("Start Aigamo!");
  
  AFMS.begin();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t i;
  
  Serial.print("tick");

  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);
  myMotor4->run(FORWARD);
  
  for (i=0; i<255; i++) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i);  
    myMotor4->setSpeed(i);  

    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i);  
    myMotor4->setSpeed(i);  

    delay(10);
  }
  
  Serial.print("tock");

  myMotor1->run(BACKWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(BACKWARD);
  myMotor4->run(BACKWARD);
  
  for (i=0; i<255; i++) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i);  
    myMotor4->setSpeed(i);  
    
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor1->setSpeed(i);  
    myMotor2->setSpeed(i);  
    myMotor3->setSpeed(i);  
    myMotor4->setSpeed(i);  
    
    delay(10);
  }

  Serial.print("tech");
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);
  
  delay(1000);
}
