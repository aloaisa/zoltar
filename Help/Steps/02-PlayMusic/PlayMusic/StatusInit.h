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

DFRobotDFPlayerMini musicDFPlayer;
SoftwareSerial musicSoftwareSerial(MUSIC_RX_PIN, MUSIC_TX_PIN); // RX, TX

void initMusicConfiguration()
{
  musicSoftwareSerial.begin(BAUDS);
  if (!musicDFPlayer.begin(musicSoftwareSerial))
  {
    while (true)
      ;
  }

  musicDFPlayer.volume(MUSIC_VOLUME);
}

void statusInit_initialize()
{
  initMusicConfiguration();
}

void playMusic()
{
  musicDFPlayer.play(1);
}

int statusInit(int status)
{
  if (isStatusInit == false)
  {
    Serial.println("INIT-1");
    playMusic();

    isStatusInit = true;

    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}
