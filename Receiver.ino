//#include "orgb417pb.h"
//
//uint8_t GPIO_Pin = D2;
//
//ORGB417PB receiver(digitalPinToInterrupt(GPIO_Pin), 3);
//unsigned long value = 0;
//
//void setup() {
//  Serial.begin(115200); 
//  Serial.println("\nReady.\n\n");
//}
//
//void loop() {
//  if (receiver.has_code()) {
//    if (value != receiver.code()) {
//      value = receiver.code();
//      Serial.print("Found: ");
//      Serial.print(value);
//      Serial.print(" - ");
//      Serial.println(value, BIN);
//    }
//    receiver.clear_code();
//  }
//}

#include "orgb417pb.h"

uint8_t GPIO_Pin = D2;

ORGB417PB transciver(digitalPinToInterrupt(GPIO_Pin), D0);

void setup() {
  Serial.begin(115200);
}

void loop() {
  transciver.send(16575493, 4);
  delay(1000);

  if (transciver.has_code()) {
    Serial.println(transciver.code());
    transciver.clear_code();
  }

  transciver.send(16266309, 4);
  delay(1000);

  if (transciver.has_code()) {
    Serial.println(transciver.code());
    transciver.clear_code();
  }
}
