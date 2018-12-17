/**
 * Stand by:
 * When the game is waiting to start the game.
 * Check if the coin enter - 1 digital input
 * When coin in, then start game.
 */
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
    delay(500);
    digitalWrite(ENABLE_COIN_MACHINE_PIN, LOW);
  }

  return status;
}
