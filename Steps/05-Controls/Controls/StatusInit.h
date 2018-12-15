/**
 * Init status:
 * only run one time per game.
 * Play background music - 2 Digital-analogical inputs
 * On background leds - 1 digital input
 * And wait a defined time to start the game
 */
boolean isStatusInit = false;

DFRobotDFPlayerMini musicDFPlayer;
SoftwareSerial musicSoftwareSerial(MUSIC_RX_PIN, MUSIC_TX_PIN); // RX, TX

void initMusicConfiguration() {
  musicSoftwareSerial.begin(BAUDS);
  if (!musicDFPlayer.begin(musicSoftwareSerial)) {
    while (true)
      ;
  }

  musicDFPlayer.volume(MUSIC_VOLUME);
}

void playMusic() {
  musicDFPlayer.play(1);
}

void playEyesSound() {
  musicDFPlayer.play(2);
}

int statusInit(int status) {
  if (isStatusInit == false) {
    Serial.println("STATUS_INIT...");
    
    Serial.println("Init nano...");
    nano_On();

    Serial.println("Play Chispas sound...");
    playEyesSound(); // En el nano se encienden los ojos a la vez
    delay(1000);

    Serial.println("Play Music...");
    playMusic(); // La cebeza se debe mover en el nano a la vez.
    delay(2000);

    isStatusInit = true;

    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}

void statusInit_Reset()
{
  isStatusInit = false;
}
