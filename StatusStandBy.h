/**
 * Stand by:
 * When the game is waiting to start the game.
 * Check if the coin enter - 1 digital input
 * When coin in, then start game.
 */
int statusStandBy(int status)
{

  // TODO Activar/Desactivar máquina de monedas
  // ENABLE_COIN_MACHINE_PIN

  int inputCoin = digitalRead(DETECT_COIN_PIN);
  if (inputCoin == HIGH)
  {
    status = STATUS_INIT;
    delay(DELAY_AFTER_STATUS_INIT); // meter espera entre moneda y movimiento de la cabeza
  }

  return status;
}
