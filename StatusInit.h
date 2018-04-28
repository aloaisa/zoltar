/**
 * Init status:
 * only run one time per game.
 * Play background music - 2 Digital-analogical inputs
 * On background leds - 1 digital input
 * On eyes leds - 1 digital input
 * On mouth move - 1 digital input
 * And wait a defined time to start the game
 */
boolean isStatusInit = false;
boolean mouthMove;

DFRobotDFPlayerMini musicDFPlayer;
SoftwareSerial musicSoftwareSerial(MUSIC_RX_PIN, MUSIC_TX_PIN); // RX, TX

void statusInit_initMusicConfiguration() {
    musicSoftwareSerial.begin(BAUDS);
    if (!musicDFPlayer.begin(musicSoftwareSerial)) {
      while(true);
    }
    
    musicDFPlayer.volume(MUSIC_VOLUME);
}

void playMusic() {
  musicDFPlayer.play(1);
}

void backgroundLedOn() {  
  digitalWrite(BACKGROUND_LED_PIN, HIGH);
}

void eyesLedOn() {
  digitalWrite(EYES_LED_PIN, HIGH);
}

void statusInit_initHeadMove() {
  mouthMove = false;  
}

void mouthMoveOn() {
  mouthMove = true;
}

boolean statusInit_headMoveIsActive() {
  return mouthMove;
}

void statusInit_moveHead() {
  // TODO
}

int statusInit(int status) {
  if (isStatusInit == false) {
    // TODO Activate music
    //playMusic();
    backgroundLedOn();
    eyesLedOn();
    mouthMoveOn();
    
    isStatusInit = true;
  
    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}

