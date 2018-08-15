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

Servo headServoMotor;

void statusInit_initialize()
{
  initMusicConfiguration();
  initHeadMove();
}

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

void playMusic()
{
  musicDFPlayer.play(1);
}

void eyesLedOn()
{
  digitalWrite(EYES_LED_PIN, HIGH);
}

void eyesLedOff()
{
  digitalWrite(EYES_LED_PIN, LOW);
}

void initHeadMove()
{
  headServoMotor.attach(HEAD_SERVO_PIN);
  headServoMotor.write(0);
  delay(1000);

  mouthMove = false;
}

void mouthMoveOn()
{
  mouthMove = true;
}

boolean statusInit_headMoveIsActive()
{
  return mouthMove;
}

void statusInit_moveHead()
{
  // TODO Iniciar Servo Cabeza
  // Mover servo arriba y abajo continuo
}

void statusInit_Reset()
{
  isStatusInit = false;
  initHeadMove();
  eyesLedOff();
}

int statusInit(int status)
{
  if (isStatusInit == false)
  {
    playMusic();
    eyesLedOn();
    mouthMoveOn();

    isStatusInit = true;

    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}
