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
unsigned long finishTime;

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

void pushButtonCoinLedOn() {
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, HIGH); // "Push coin button" Leds on
}

void activateControlls() {
   // TODO
}

void desactivateControlls() {
  // TODO
}

int statusActivateGame(int status) { 
  if (isStatusActivateGame == false) {
    pointToMouthLedOn();
    playSound();
    activateControlls();

    finishTime = millis() + POINT_TO_MOUTH_WAIT_TIME;
    isStatusActivateGame = true;
  }
  
  // TODO change 
  // delay(10000);
  if (finishTime < millis()) {
    desactivateControlls();
    pushButtonCoinLedOn();
    
    status = STATUS_WAITING_RELEASE_COIN;
  }
  
  return status;
}


