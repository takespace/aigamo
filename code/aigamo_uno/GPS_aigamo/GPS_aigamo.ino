//GPS test for aigamo
//uno
#include <SoftwareSerial.h>

#define RX 10
#define TX 11

SoftwareSerial mySerial(RX,TX);

void setupSoftwareSerial(){
    mySerial.begin(9600);
}

void setup(){
 Serial.begin(57600);
 while(!Serial){
 
  }

  Serial.println("Hello");
  setupSoftwareSerial();
}

void loop(){
 if(mySerial.available()){
   Serial.write(mySerial.read());
 } 
}
