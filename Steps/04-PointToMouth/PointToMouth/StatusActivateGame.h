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
SoftwareSerial soundSoftwareSerial(SOUND_RX_PIN, SOUND_TX_PIN); // RX, TX

boolean isStatusActivateGame = false;
unsigned long finishTime;
boolean isWishLedOn = false;

void initSoundConfiguration()
{
  soundSoftwareSerial.begin(BAUDS);
  if (!soundDFPlayer.begin(soundSoftwareSerial))
  {
    while (true)
      ;
  }

  soundDFPlayer.volume(SOUND_VOLUME);
}

void statusActivateGame_init()
{
  initSoundConfiguration();
}

void pointToMouthLedOn()
{
  digitalWrite(POINT_TO_MOUTH_LED_PIN, HIGH);
}

void makeAWishLedOn()
{
  if (isWishLedOn == false)
  {
    isWishLedOn = true;
    digitalWrite(MAKE_WISH_LED_PIN, HIGH);
  }
}

void pushButtonCoinLedOn()
{
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, HIGH);
}

void playSound()
{
  soundDFPlayer.play(1);
}

int statusActivateGame(int status)
{
  if (isStatusActivateGame == false)
  {
    playSound();
    pointToMouthLedOn();

    finishTime = millis() + POINT_TO_MOUTH_WAIT_TIME + MAKE_WITH_WAIT_TIME;
    isStatusActivateGame = true;
  }

  // Se enciende pide un deseo, pero puedes seguir moviendolo hasta otros
  // Activa los leds de pide un deseo.
  if ((finishTime - MAKE_WITH_WAIT_TIME) <= millis())
  {
    makeAWishLedOn();
  }

  if (finishTime <= millis())
  {
    pushButtonCoinLedOn();

    status = STATUS_WAITING_RELEASE_COIN;
  }

  return status;
}
