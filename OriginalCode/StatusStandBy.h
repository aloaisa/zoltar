/**
 * Stand by:
 * When the game is waiting to start the game.
 * Check if the coin enter - 1 digital input
 * When coin in, then start game.
 */

void statusInit_StandBy() {
  digitalWrite(ENABLE_COIN_MACHINE_PIN, HIGH);
}

int statusStandBy(int status)
{

  // TODO Activar/Desactivar máquina de monedas
  // ENABLE_COIN_MACHINE_PIN = 7;

  int inputCoin = digitalRead(DETECT_COIN_PIN);
  if (inputCoin == LOW)
  {
    status = STATUS_INIT;
    delay(DELAY_AFTER_STATUS_INIT); // meter espera entre moneda y movimiento de la cabeza
  }

  return status;
}
