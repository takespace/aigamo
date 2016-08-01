#include <SoftwareSerial.h>

//parameter for communication with controller
#define RX2 12
#define TX2 13


SoftwareSerial controllerSerial(RX2,TX2);


void setup() {
  // put your setup code here, to run once:
  controllerSerial.begin(115200);
  Serial.begin(115200);
}

void loop() {
  if (controllerSerial.available()) Serial.write(controllerSerial.read());

}




