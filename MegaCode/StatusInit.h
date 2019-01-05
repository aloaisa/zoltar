boolean isStatusInit;

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

    Serial.println("Play eyes on sound...");
    playEyesSound();
    delay(TIME_BETWEEN_EYES_SOUND_AND_PLAY_MUSIC);

    Serial.println("Play Music...");
    playMusic();

    delay(TIME_BETWEEN_PLAY_MUSIC_AND_START_GAME);

    isStatusInit = true;

    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}

void statusInit_Reset() {
  isStatusInit = false;
}
