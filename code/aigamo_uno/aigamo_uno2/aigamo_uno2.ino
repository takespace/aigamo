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
  Serial.begin(115200);
  Serial.setTimeout(5000);
  
  Serial.println("Start Aigamo!");
  
  AFMS.begin();
  
  
}

void loop() {
  char command;
  int data;
  if (CommTask(&command, &data))
  {
    switch (command)
    {
    case 'F': // Forward
        Serial.println("get F command");
        myMotor1->run(FORWARD);
        myMotor1->setSpeed(200); 
        delay(100);
        myMotor1->setSpeed(0); 

      break;
    case 'B': // Backward
        Serial.println("get B command");

        myMotor1->run(BACKWARD);
        myMotor1->setSpeed(200);
         delay(100);
        myMotor1->setSpeed(0);

      break;
    case 'S': // Stop
      break;
    case 'L': // Left
      break;
    case 'R': // Right
      break;
    case 'c': // TurnCw
      break;
    case 'C': // TurnCcw
      break;
      
    default:
        myMotor1->run(FORWARD);
        myMotor1->setSpeed(0);          
    }
  }
}






boolean CommTask(char* command, int* data)
{
  if (Serial.available() <= 0) return false;
  if (Serial.read() != ':') return false;
  
  String message = Serial.readStringUntil('\n');
  if (message.length() != 1 + 2) return false;

  int i = 0;
  String c = message.substring(i, i + 1); i += 1;
  String d = message.substring(i, i + 2); i += 2;

  *command = c[0];
  if (sscanf(d.c_str(), "%x", data) != 1) return false;

  return true;
}
