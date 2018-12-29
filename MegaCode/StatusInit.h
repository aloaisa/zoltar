boolean isStatusInit = false;
unsigned long off_nano_time;

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

boolean isLastCardsSwitchActivate() {
  boolean result = false;

  int lostCards = digitalRead(SWITCH_NEED_CARDS_LOST_CARD_MOTOR_PIN);
  int winCards = digitalRead(SWITCH_NEED_CARDS_WIN_CARD_MOTOR_PIN);
  if (lostCards == HIGH || winCards == HIGH) {
    result = true;
  }

  return result;
}

int statusInit(int status) {
  if (isStatusInit == false) {
    Serial.println("STATUS_INIT...");
    
    if (isLastCardsSwitchActivate() == true) {
      playRefillCardSound();
    }

    Serial.println("Init nano...");
    nano_On();

    Serial.println("Play eyes on sound...");
    playEyesSound();
    delay(TIME_BETWEEN_EYES_SOUND_AND_PLAY_MUSIC);

    Serial.println("Play Music...");
    playMusic();

    off_nano_time = millis() + TOTAL_MUSIC_TIME;
    delay(TIME_BETWEEN_PLAY_MUSIC_AND_START_GAME);

    isStatusInit = true;

    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}

void statusInit_Reset() {
  isStatusInit = false;
}
