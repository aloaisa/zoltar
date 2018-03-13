/**
 * Init status:
 * only run one time per game.
 * Play background music - 2 Digital-analogical inputs
 * On background leds - 1 digital input
 * On eyes leds - 1 digital input
 * On mouth move - 1 digital input
 * And wait a defined time to start the game
 */
DFRobotDFPlayerMini musicDFPlayer;
boolean isStatusInit = false;
SoftwareSerial musicSoftwareSerial(MUSIC_RX_PIN, MUSIC_TX_PIN); // RX, TX

void initMusicConfiguration() {
    musicSoftwareSerial.begin(BAUDS);
    if (!musicDFPlayer.begin(musicSoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      while(true);
    }
    
    musicDFPlayer.volume(MUSIC_VOLUME);
}

void playMusic() {
  musicDFPlayer.play(1);  //Play the first mp3
}

void backgroundLedOn() {  
  digitalWrite(BACKGROUND_LED_PIN, HIGH);
}

void eyesLedOn() {
  digitalWrite(EYES_LED_PIN, HIGH);
}

void mouthMoveOn() {
  // TODO
}

int statusInit(int status) {
  if (isStatusInit == false) {
    playMusic();
    backgroundLedOn();
    eyesLedOn();
    mouthMoveOn();
    
    isStatusInit = true;

    delay(DELAY_AFTER_STATUS_INIT);
  
    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}

