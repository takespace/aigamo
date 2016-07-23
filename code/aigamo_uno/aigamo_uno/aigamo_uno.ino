#include <Arduino.h>
#include <Wire.h>
#include <DRV8830MotorDriver.h>
#include <SoftwareSerial.h>
#include "NAxisMotion.h"
#include <math.h>

//Object that for the sensor
NAxisMotion mySensor;
float Direction = 0;




DRV8830MotorDriver motor1(DRV8830_A1_A0_0_0);
DRV8830MotorDriver motor2(DRV8830_A1_A0_0_1);
DRV8830MotorDriver motor3(DRV8830_A1_A0_1_0);
DRV8830MotorDriver motor4(DRV8830_A1_A0_1_1);

//Parameter for motor
#define FAULTn  7

//parameter for GPS
#define RX 10
#define TX 11

SoftwareSerial gpsSerial(RX,TX);


void setup()
{
  Serial.begin(57600);//Serial for PC
  gpsSerial.begin(9600);//communication for GPS
  Wire.begin();//communication for I2C
  Serial.println("Hello, Aigamo interface");

  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);

  /* Sensor Initialization */
  //Can be configured to other operation modes as desired
  mySensor.initSensor();

  //The default is AUTO. Changing to manual requires calling the relevant update functions prior to calling the read functions
  mySensor.setOperationMode(OPERATION_MODE_NDOF);

  //Setting to MANUAL requires lesser reads to the sensor
  mySensor.setUpdateMode(MANUAL);  
}

int spd = 0;

void loop()
{
  //IMU update
  mySensor.updateMag();
  mySensor.updateCalibStatus();  	//Update the Calibration Status

  //display IMU value
  Serial.print(" X: ");
  Serial.print(mySensor.readMagX()); //Heading data
  Serial.print("deg ");

  Serial.print(" Y: ");
  Serial.print(mySensor.readMagY()); //Roll data
  Serial.print("deg");

  Serial.print(" Z: ");
  Serial.print(mySensor.readMagZ()); //Pitch data
  Serial.print("deg ");

  Serial.print(" M: ");
  Serial.println(mySensor.readMagCalibStatus());    //Magnetometer Calibration Status (0 - 3)

            
            
  Direction = atan2(mySensor.readMagX(),mySensor.readMagY())/3.14*180;
  Serial.print(Direction);

  Serial.println();

  //  
  
 if(gpsSerial.available()){
   Serial.write(gpsSerial.read());
 }  
  char c;

  if (Serial.available())
  {
    c = Serial.read();
    if (c == '+')
    {
      spd++;
      motor1.setSpeed(spd);
      motor2.setSpeed(spd);
      motor3.setSpeed(spd);
      motor4.setSpeed(spd);
      spd = motor1.getSpeed();
      Serial.println(spd);
    }
    else if (c == '-')
    {
      spd--;
      motor1.setSpeed(spd);
      motor2.setSpeed(spd);
      motor3.setSpeed(spd);
      motor4.setSpeed(spd);
      spd = motor1.getSpeed();
      Serial.println(spd);
    }
    else if (c == 'b')
    {
      spd = 0;
      motor1.setSpeed(spd);
      motor2.setSpeed(spd);
      motor3.setSpeed(spd);
      motor4.setSpeed(spd);
      motor1.brake();
      motor2.brake();
      motor3.brake();
      motor4.brake();
      spd = motor1.getSpeed();
      Serial.println(spd);
    }
  }
}


