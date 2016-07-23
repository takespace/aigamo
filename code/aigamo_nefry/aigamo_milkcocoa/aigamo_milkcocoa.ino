#include <Nefry.h>
#include <Nefry_Milkcocoa.h>

Nefry_Milkcocoa *milkcocoa;
void onpush(DataElement *elem);

void setup() {
  milkcocoa->print();//Setup ModuleにAPPIDの表示をする
  milkcocoa = Nefry_Milkcocoa::begin("iceinixlzq3", "PNKKHFEPCKAFILFM", "RlRkEPWLBdQYdOjNUYgaOILVkWYfSVMChOnYKRGX");
  Nefry.println( milkcocoa->on("aigamo", "send", onpush) ? "Milkcocoa onPush OK" : "Milkcocoa onPush NG" );
}

void loop() {
  Nefry.println( milkcocoa->loop(10000) ? "Milkcocoa Connect OK" : "Milkcocoa Connect NG" );
}

void onpush(DataElement *elem) {//MilkcocoaのOn関数と同一
  Serial.print("motor:");
  Nefry.print(elem->getInt("on"));//回転方向 -1:後退　0:停止　1:前進
  Serial.print(":");
  Nefry.print(elem->getString("motor"));//どちらのモータか r or l
  Serial.print(":");
  Nefry.print(elem->getInt("speed"));//速度 0-255
}
