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

DFRobotDFPlayerMini soundDFPlayer;
boolean isStatusActivateGame = false;
SoftwareSerial soundSoftwareSerial(SOUND_RX_PIN, SOUND_TX_PIN); // RX, TX

void initSoundConfiguration() {
    soundSoftwareSerial.begin(BAUDS);
    if (!soundDFPlayer.begin(soundSoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      while(true);
    }
    
    soundDFPlayer.volume(SOUND_VOLUME);
}

void pointToMouthLedOn() {  
  digitalWrite(POINT_TO_MOUTH_LED_PIN, HIGH);
}

void playSound() {
  soundDFPlayer.play(1);  //Play the first mp3
}

int statusActivateGame(int status) { 
  if (isStatusActivateGame == false) {
    pointToMouthLedOn();
    playSound();
    // Activar los mandos
    
    //delay(10000);
  
    // Desactivar los mandos
    // Encender luces "Pulsa botón liberar moneda"
    // Activo siguiente estado WAITING_RELEASE_COIN
    
    isStatusActivateGame = true;
    status = STATUS_WAITING_RELEASE_COIN;
  }
  
  return status;
}


