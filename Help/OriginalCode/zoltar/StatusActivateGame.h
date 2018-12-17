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
Servo verticalServo;
Servo horizontalServo;

int verticalPos;
int horizontalPos;

DFRobotDFPlayerMini soundDFPlayer;
SoftwareSerial soundSoftwareSerial(SOUND_RX_PIN, SOUND_TX_PIN); // RX, TX

boolean isStatusActivateGame = false;
unsigned long finishTimeGame;
boolean controlsActive;
int clkLastSignal, clkLastSignal2;

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

void initServoConfiguration()
{
  verticalServo.attach(SERVO_VERTICAL_PIN);
  verticalServo.write(0);
  delay(1000);

  horizontalServo.attach(SERVO_HORIZONTAL_PIN);
  horizontalServo.write(0);
  delay(1000);

  /* Read Pin A and B
   Whatever state it's in will reflect the last position   
   */
  verticalPos = digitalRead(CONTROLS_VERTICAL_CLK_PIN);
  horizontalPos = digitalRead(CONTROLS_HORIZONTAL_CLK_PIN);
}

void statusActivateGame_init()
{
  // TODO Does not works!
  // initSoundConfiguration();

  initServoConfiguration();
}

void pointToMouthLedOn()
{
  digitalWrite(POINT_TO_MOUTH_LED_PIN, HIGH);
}

void makeAWishLedOn()
{
  digitalWrite(MAKE_WISH_LED_PIN, HIGH);
}

void makeAWishLedOff()
{
  digitalWrite(MAKE_WISH_LED_PIN, HIGH);
}

void playSound()
{
  soundDFPlayer.play(1);
}

void pushButtonCoinLedOn()
{
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, HIGH);
}

void activateControlls()
{
  controlsActive = true;
}

void desactivateControlls()
{
  controlsActive = false;
}

boolean isControlsActive()
{
  return controlsActive;
}

void moveControls()
{
  int clkSignal = digitalRead(CONTROLS_VERTICAL_CLK_PIN);
  int dtSignal = digitalRead(CONTROLS_VERTICAL_DT_PIN);

  int servoMove = verticalServo.read();
  if (clkSignal != clkLastSignal && clkSignal != clkLastSignal2)
  {

    if (dtSignal == HIGH)
    {
      //Serial.println("Izquierda");
      verticalPos = verticalPos + 1;
      if (verticalPos > 158)
      {
        verticalPos = 158;
      }
    }
    else
    {
      //Serial.println("Derecha");
      verticalPos = verticalPos - 1;
      if (verticalPos < 0)
      {
        verticalPos = 0;
      }
    }

    Serial.println(verticalPos);
    verticalServo.write(verticalPos);
    delay(100);

    clkLastSignal2 = clkLastSignal;
  }

  clkLastSignal = clkSignal;
}

void statusActivateGame_Reset()
{
  isStatusActivateGame = false;
  desactivateControlls();

  // Move servos to 0 position
  for (int initPoint = 158; initPoint >= 0; initPoint--)
  {
    verticalServo.write(initPoint);
    horizontalServo.write(initPoint);
    delay(15);
  }
  verticalPos = 0;
  horizontalPos = 0;
}

int statusActivateGame(int status)
{
  if (isStatusActivateGame == false)
  {
    playSound();
    pointToMouthLedOn();
    activateControlls();

    finishTimeGame = millis() + POINT_TO_MOUTH_WAIT_TIME + MAKE_WITH_WAIT_TIME;
    isStatusActivateGame = true;
  }

  // Se enciende pide un deseo, pero puedes seguir moviendolo hasta otros
  // Activa los leds de pide un deseo.
  if ((finishTimeGame - MAKE_WITH_WAIT_TIME) < millis())
  {
    makeAWishLedOn();
  }

  if (finishTimeGame < millis())
  {
    desactivateControlls();
    pushButtonCoinLedOn();

    status = STATUS_WAITING_RELEASE_COIN;
  }

  if (isControlsActive() == true)
  {
    moveControls();
  }

  return status;
}
