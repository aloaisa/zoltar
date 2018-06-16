#include "Arduino.h"

int pin = 9;

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
}

void loop() {

  int input = digitalRead(pin);
  if (input == HIGH) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
  
}
