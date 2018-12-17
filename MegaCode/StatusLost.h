/**
 * Status Lost:
 * Move motor with lost cards
 * Stop motor when switch sensor ON and OFF again.
 */
String lastLostPosition;

void initStatusLost() {
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  digitalWrite(MOTOR_LOST_DIR_PIN, LOW);
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

  lastLostPosition = "OFF";
  digitalWrite(MOTOR_ENABLE_PIN, LOW);

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