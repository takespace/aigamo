#include <Arduino.h>
#include <Wire.h>
#include <DRV8830MotorDriver.h>
#include <SoftwareSerial.h>
#include "NAxisMotion.h"
#include <math.h>


//To stream at 25Hz without using additional timers (time period(ms) =1000/frequency(Hz))
const int streamPeriod = 1000;//40

//To store the last streamed time stamp
unsigned long lastStreamTime = 0;

//Object that for the sensor
NAxisMotion mySensor;
float Direction = 0;

//for reading value through serial
char CommandLine[300];
char ReadChar;
int counter = 0;

//value for read motor speed
int on;
int speed;
char motor;


DRV8830MotorDriver motor1(DRV8830_A1_A0_0_0);
DRV8830MotorDriver motor2(DRV8830_A1_A0_0_1);
DRV8830MotorDriver motor3(DRV8830_A1_A0_1_0);
DRV8830MotorDriver motor4(DRV8830_A1_A0_1_1);

//Parameter for motor
#define FAULTn  7

//parameter for GPS
#define RX1 10
#define TX1 11

//parameter for communication with controller
#define RX2 12
#define TX2 13

SoftwareSerial gpsSerial(RX1,TX1);

SoftwareSerial controllerSerial(RX2,TX2);


void setup()
{
  Serial.begin(115200);//Serial for PC
  //gpsSerial.begin(9600);//communication for GPS
  controllerSerial.begin(115200);
  
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


void loop()
{
 //Motor poling 

  while(controllerSerial.available() > 0){
    ReadChar = controllerSerial.read();
    CommandLine[counter] = ReadChar;
    if(ReadChar == '\n'){
      Serial.println();
      Serial.println(CommandLine);
      
      sscanf(CommandLine, "motor:%d:%c:%d", &on, &motor, &speed);

   Serial.println();
   Serial.println(on);
   Serial.println(motor);
   Serial.println(speed);
 
   motor1.setSpeed(speed);
   motor2.setSpeed(speed);
   motor3.setSpeed(speed);
   motor4.setSpeed(speed);
 
      counter = 0;
      break;
    }else{
      counter++;
    }
  }  
  
 //Sensor poling
 if((millis() - lastStreamTime) >= streamPeriod){
  lastStreamTime = millis();    

  
  //IMU update
  mySensor.updateMag();
  mySensor.updateCalibStatus();  	//Update the Calibration Status

  Serial.println("");
  Serial.println("");
  Serial.println("");


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
 while(gpsSerial.available()){ 
// if(gpsSerial.available()){
   Serial.write(gpsSerial.read());
 }  

 }//if or while
}

void RunMotor(char r, int spd){
  
  
}

