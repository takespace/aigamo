//Contains the bridge code between the API and the Arduino Environment
#include "NAxisMotion.h"
#include <Wire.h>
#include <math.h>

//Object that for the sensor
NAxisMotion mySensor;

//To store the last streamed time stamp
unsigned long lastStreamTime = 0;

//To stream at 25Hz without using additional timers (time period(ms) =1000/frequency(Hz))
const int streamPeriod = 40;

float Direction = 0;

//Flag to update the sensor data. Default is true to perform the first read before the first stream
bool updateSensorData = true;

void setup() { //This code is executed once
	//Peripheral Initialization
	//Initialize the Serial Port to view information on the Serial Monitor
	Serial.begin(115200);

	//Initialize I2C communication to the let the library communicate with the sensor. 
	//The I2C Address can be changed here inside this function in the library
	Wire.begin();

	/* Sensor Initialization */
	//Can be configured to other operation modes as desired
	mySensor.initSensor();

	//The default is AUTO. Changing to manual requires calling the relevant update functions prior to calling the read functions
	mySensor.setOperationMode(OPERATION_MODE_NDOF);

	//Setting to MANUAL requires lesser reads to the sensor
	mySensor.setUpdateMode(MANUAL);
}

void loop() { //This code is looped forever
	if ((millis() - lastStreamTime) >= streamPeriod) {
		lastStreamTime = millis();    
		mySensor.updateEuler();        		//Update the Euler data into the structure of the object
                mySensor.updateMag();
		mySensor.updateCalibStatus();  	//Update the Calibration Status

		Serial.print("Time: ");
		Serial.print(lastStreamTime);
		Serial.print("ms ");

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
	}
}
