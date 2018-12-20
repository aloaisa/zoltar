void nano_Off() {
  digitalWrite(NANO_PIN, LOW);
}

void statusInit_StandBy() {
  nano_Off();
  digitalWrite(ENABLE_COIN_MACHINE_PIN, HIGH);
}

void nano_On() {
  digitalWrite(NANO_PIN, HIGH);
}

int statusStandBy(int status) {
  int inputCoin = digitalRead(DETECT_COIN_PIN);

  if (inputCoin == HIGH) {
    status = STATUS_INIT;
    delay(TIME_BETWEEN_INSERT_COIN_AND_START_INIT_GAME);
    digitalWrite(ENABLE_COIN_MACHINE_PIN, LOW);
  }

  return status;
}
