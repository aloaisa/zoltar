/**
 * Stand by:
 * When the game is waiting to start the game.
 * Check if the coin enter - 1 digital input
 * When coin then start game.
 */
// Input: Detectar moneda
int statusStandBy(int status) {

  // Esperando a que llegue la señal de la moneda
  // Y cambio al siguiente estado INIT al detectarla

  int inputCoin = digitalRead(DETECT_COIN_PIN);
  if (inputCoin == HIGH) {
    status = STATUS_INIT;
  }

  return status;
}

