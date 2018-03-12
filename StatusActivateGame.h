/**
 * Activate game:
 * On leds "Point to the mouth" - 1 digital input
 * On sound - 2 Digital-analogical inputs
 * On controls - 2 Analagical inputs
 * Activate under the controls 2 servos (x, y) - 2 digital inputs
 * Wait a time to user play game moving the controls.
 * Disable controls
 * On leds "Press the button"
 * Activate next status
 */
void pointToMouthLedOn() {  
  digitalWrite(POINT_TO_MOUTH_LED_PIN, HIGH);
}

int statusActivateGame(int status) { 
  pointToMouthLedOn();
  // Encender sonido campana
  // Activar los mandos
  
  //delay(10000);

  // Desactivar los mandos
  // Encender luces "Pulsa botón liberar moneda"
  // Activo siguiente estado WAITING_RELEASE_COIN

  return status;
}


