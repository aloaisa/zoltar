/**
 * Stand by:
 * When the game is waiting to start the game.
 * Check if the coin enter - 1 digital input
 * When coin in, then start game.
 */
int statusStandBy(int status) {
  
  int inputCoin = digitalRead(DETECT_COIN_PIN);
  if (inputCoin == HIGH) {
    status = STATUS_INIT;
  }

  return status;
}

