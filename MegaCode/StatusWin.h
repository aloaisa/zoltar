String lastWinPosition;

void initStatusWin() {
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  digitalWrite(MOTOR_WIN_DIR_PIN, LOW);
  digitalWrite(MOTOR_WIN_STEP_PIN, LOW);
}

boolean moveWinCardMotor() {
  boolean result = true;

  int input = digitalRead(SWITCH_WIN_CARD_MOTOR_PIN);
  if (input == HIGH) {
    lastWinPosition = "ON";
  } else {
    if (lastWinPosition == "ON") {
      result = false;
    }

    lastWinPosition = "OFF";
  }

  return result;
}

int statusWin(int status) {
 
  lastWinPosition = "OFF";
  digitalWrite(MOTOR_ENABLE_PIN, LOW);

  playWinCard();
  
  while (moveWinCardMotor() == true) {
    Serial.println("Moving motor win cards...");

    digitalWrite(MOTOR_WIN_STEP_PIN, HIGH);
    delay(MOTOR_STEP_VELOCITY_DELAY);
    digitalWrite(MOTOR_WIN_STEP_PIN, LOW);
    delay(MOTOR_STEP_VELOCITY_DELAY);
  }

  digitalWrite(MOTOR_ENABLE_PIN, HIGH);

  status = STATUS_OFF;
  return status;
}