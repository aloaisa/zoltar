#include "Arduino.h"

void setup() {
  Serial.begin(9600);
  
}

void loop() {

  int input = digitalRead(37);
  if (input == HIGH) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  
}
