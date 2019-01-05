String lastLostPosition;

void initStatusLost() {
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  digitalWrite(MOTOR_LOST_DIR_PIN, HIGH);
  digitalWrite(MOTOR_LOST_STEP_PIN, LOW);
}

boolean moveLostCardMotor() {
  boolean result = true;

  int input = digitalRead(SWITCH_LOST_CARD_MOTOR_PIN);
  if (input == HIGH) {
    lastLostPosition = "ON";
  } else {
    if (lastLostPosition == "ON") {
      result = false;
    }

    lastLostPosition = "OFF";
  }

  return result;
}

int statusLost(int status) {

  detachInterrupt(digitalPinToInterrupt(SENSOR_WIN_PIN));

  lastLostPosition = "OFF";
  digitalWrite(SOLENOID_PIN, LOW);
  digitalWrite(MOTOR_ENABLE_PIN, LOW);
  playLostCard();
  
  while (moveLostCardMotor() == true) {
    Serial.println("Moving motor lost cards...");

    digitalWrite(MOTOR_LOST_STEP_PIN, HIGH);
    delay(MOTOR_STEP_VELOCITY_DELAY);
    digitalWrite(MOTOR_LOST_STEP_PIN, LOW);
    delay(MOTOR_STEP_VELOCITY_DELAY);
  }

  digitalWrite(MOTOR_ENABLE_PIN, HIGH);

  status = STATUS_OFF;
  return status;
}