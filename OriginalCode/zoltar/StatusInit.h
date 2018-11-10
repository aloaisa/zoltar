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

// DFRobotDFPlayerMini musicDFPlayer;
// SoftwareSerial musicSoftwareSerial(MUSIC_RX_PIN, MUSIC_TX_PIN); // RX, TX

Servo headServoMotor;
int servoHeadPosition = 0;
int servoDirection = 1;

void initMusicConfiguration()
{
  // musicSoftwareSerial.begin(BAUDS);
  // if (!musicDFPlayer.begin(musicSoftwareSerial))
  // {
  // while (true)
  // ;
  // }

  // musicDFPlayer.volume(MUSIC_VOLUME);
}

void initHeadMove()
{
  headServoMotor.attach(HEAD_SERVO_PIN);
  servoHeadPosition = 0;
  servoDirection = 1;
  headServoMotor.write(servoHeadPosition);
  // delay(1000);

  mouthMove = false;
}

void playMusic()
{
  // musicDFPlayer.play(1);
}

void statusInit_initialize()
{
  initMusicConfiguration();
  initHeadMove();
}

void eyesLedOn()
{
  digitalWrite(EYES_LED_PIN, HIGH);
}

void eyesLedOff()
{
  digitalWrite(EYES_LED_PIN, LOW);
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
  // TODO Iniciar movimiento Servo Cabeza
  // Mover servo arriba y abajo continuo

  servoHeadPosition = servoHeadPosition + servoDirection;

  if (servoHeadPosition > 158)
  {
    servoHeadPosition = 158;
  }

  if (servoHeadPosition < 0)
  {
    servoHeadPosition = 0;
  }

  // servoHeadPosition
  // headServoMotor.write(pos);
  // delay(100);
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
    Serial.println("INIT-1");
    playMusic();
    Serial.println("INIT-2");
    eyesLedOn();
    Serial.println("INIT-3");
    mouthMoveOn();
    Serial.println("INIT-4");

    isStatusInit = true;

    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}
