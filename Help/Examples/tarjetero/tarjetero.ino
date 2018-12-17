#include "Arduino.h"

const int MOTOR_STEP_VELOCITY_DELAY = 40;

const int MOTOR_ENABLE_PIN = 39;

// WIN PINS
const int MOTOR_STEP_PIN = 41;
const int MOTOR_DIR_PIN = 43;
const int SWITCH_CARD_MOTOR_PIN = 45;

// LOST PINS
// const int MOTOR_STEP_PIN = 40;
// const int MOTOR_DIR_PIN = 42;
// const int SWITCH_CARD_MOTOR_PIN = 44;

String lastPosition;

void setup() {

  Serial.begin(9600);
  
  // pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  // pinMode(MOTOR_STEP_PIN, OUTPUT);
  // pinMode(MOTOR_DIR_PIN, OUTPUT);
  // pinMode(SWITCH_CARD_MOTOR_PIN, INPUT);

  // digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  // digitalWrite(MOTOR_DIR_PIN, LOW);
  // digitalWrite(MOTOR_STEP_PIN, LOW);
}

void loop() {
  runMotor();
  delay(2000);
}

boolean moveCardMotor() {
  boolean result = true;

  int input = digitalRead(SWITCH_CARD_MOTOR_PIN);
  if (input == HIGH) {
    lastPosition = "ON";
  } else {
    if (lastPosition == "ON") {
      result = false;
    }

    lastPosition = "OFF";
  }

  Serial.println(lastPosition);

  return result;
}

void runMotor() {
  lastPosition = "OFF";
  // digitalWrite(MOTOR_ENABLE_PIN, LOW);

  while (moveCardMotor() == true) {
    // Serial.println("Moving motor cards...");

    // digitalWrite(MOTOR_STEP_PIN, HIGH);
    // delay(MOTOR_STEP_VELOCITY_DELAY);
    // digitalWrite(MOTOR_STEP_PIN, LOW);
    // delay(MOTOR_STEP_VELOCITY_DELAY);
  }

  // digitalWrite(MOTOR_ENABLE_PIN, HIGH);
}
