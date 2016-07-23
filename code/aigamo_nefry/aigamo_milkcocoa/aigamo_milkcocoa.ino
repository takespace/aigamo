#include <Nefry.h>
#include <Nefry_Milkcocoa.h>

Nefry_Milkcocoa *milkcocoa;

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *r = AFMS.getMotor(1);
Adafruit_DCMotor *l = AFMS.getMotor(2);

void onpush(DataElement *elem);

void setup() {
  AFMS.begin();
  milkcocoa->print();//Setup ModuleにAPPIDの表示をする
  milkcocoa = Nefry_Milkcocoa::begin("iceinixlzq3", "PNKKHFEPCKAFILFM", "RlRkEPWLBdQYdOjNUYgaOILVkWYfSVMChOnYKRGX");
  Nefry.println( milkcocoa->on("aigamo", "send", onpush) ? "Milkcocoa onPush OK" : "Milkcocoa onPush NG" );
}

void loop() {
  Nefry.println( milkcocoa->loop(10000) ? "Milkcocoa Connect OK" : "Milkcocoa Connect NG" );
}

void onpush(DataElement *elem) {//MilkcocoaのOn関数と同一
  Nefry.print("onpush:");
  Nefry.print(elem->getInt("on"));
  Nefry.print(elem->getString("motor"));
  Nefry.print(elem->getInt("speed"));
  int _on = elem->getInt("on");
  String _motor = elem->getString("motor");
  if (_motor.equals("R")) {
    Nefry.print("onpush:");
    if (_on == 0) {
      r->run(RELEASE);
    } else if (_on == 1) {
      r->run(FORWARD);
    } else if (_on == -1) {
      r->run(BACKWARD);
    }
    r->setSpeed(elem->getInt("speed"));
  } else if (_motor.equals("L")) {
    if (_on == 0) {
      l->run(RELEASE);
    } else if (_on == 1) {
      l->run(FORWARD);
    } else if (_on == -1) {
      l->run(BACKWARD);
    }
    l->setSpeed(elem->getInt("speed"));
  }
}

