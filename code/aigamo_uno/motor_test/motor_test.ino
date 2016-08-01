#include <Arduino.h>
#include <Wire.h>
#include <DRV8830MotorDriver.h>

DRV8830MotorDriver motor1(DRV8830_A1_A0_0_0);
DRV8830MotorDriver motor2(DRV8830_A1_A0_0_1);
DRV8830MotorDriver motor3(DRV8830_A1_A0_1_0);
DRV8830MotorDriver motor4(DRV8830_A1_A0_1_1);

#define FAULTn  7

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Hello,DRV8830 I2C MotorDriver");

  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

int spd = 0;

void loop()
{
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
//void checkMotorErr() {
//  if (digitalRead(FAULTn) == HIGH)return;
//  Wire.beginTransmission(motor1);
//  Wire.write(0x01);
//  Wire.endTransmission();
//
//  Wire.requestFrom(motor0, 1);
//  byte err = Wire.read();
//  if (err & 0b00000011) {
//    Serial.println("over current");
//  } else if (err & 0b00000101) {
//    Serial.println("under voltage");
//  } else if (err & 0b00001001) {
//    Serial.println("over heat");
//  } else if (err & 0b00010001) {
//    Serial.println("limit current");
//  }
//  clearErr();
//}
//void clearErr() {
//  Wire.beginTransmission(motor1);
//  Wire.write(0x01);
//  Wire.write(0x80);
//}

