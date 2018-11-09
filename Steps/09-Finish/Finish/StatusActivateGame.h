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

Servo verticalServo;
Servo horizontalServo;

boolean controlsActive;
int verticalPos, horizontalPos;
int clkLastVerticalSignal, clkLastVerticalSignal2;
int clkLastHorizontalSignal, clkLastHorizontalSignal2;

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
  delay(2000);

  horizontalServo.attach(SERVO_HORIZONTAL_PIN);
  horizontalServo.write(0);
  delay(2000);

  /* Read Pin A and B
   Whatever state it's in will reflect the last position   
   */
  verticalPos = digitalRead(CONTROLS_VERTICAL_CLK_PIN);
  horizontalPos = digitalRead(CONTROLS_HORIZONTAL_CLK_PIN);
}

void statusActivateGame_init()
{
  initSoundConfiguration();
  initServoConfiguration();
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

void makeAWishLedOff()
{
  digitalWrite(MAKE_WISH_LED_PIN, LOW);
}

void pushButtonCoinLedOn()
{
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, HIGH);
}

void pushButtonCoinLedOff()
{
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, LOW);
}

void playSound()
{
  soundDFPlayer.play(1);
}

void activateControls()
{
  controlsActive = true;
}

void desactivateControls()
{
  controlsActive = false;
}

boolean isControlsActive()
{
  return controlsActive;
}

void moveVerticalControl()
{
  int clkSignal = digitalRead(CONTROLS_VERTICAL_CLK_PIN);
  int dtSignal = digitalRead(CONTROLS_VERTICAL_DT_PIN);

  if (clkSignal != clkLastVerticalSignal && clkSignal != clkLastVerticalSignal2)
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

    verticalServo.write(verticalPos);
    clkLastVerticalSignal2 = clkLastVerticalSignal;
  }

  clkLastVerticalSignal = clkSignal;
}

void moveHorizonalControl()
{
  int clkSignal = digitalRead(CONTROLS_HORIZONTAL_CLK_PIN);
  int dtSignal = digitalRead(CONTROLS_HORIZONTAL_DT_PIN);

  if (clkSignal != clkLastHorizontalSignal && clkSignal != clkLastHorizontalSignal2)
  {

    if (dtSignal == HIGH)
    {
      //Serial.println("Izquierda");
      horizontalPos = horizontalPos + 1;
      if (horizontalPos > 158)
      {
        horizontalPos = 158;
      }
    }
    else
    {
      //Serial.println("Derecha");
      horizontalPos = horizontalPos - 1;
      if (horizontalPos < 0)
      {
        horizontalPos = 0;
      }
    }

    verticalServo.write(horizontalPos);
    clkLastHorizontalSignal2 = clkLastHorizontalSignal;
  }

  clkLastHorizontalSignal = clkSignal;
}

void moveControls()
{
  moveVerticalControl();
  moveHorizonalControl();
}

int statusActivateGame(int status)
{
  if (isStatusActivateGame == false)
  {
    playSound();
    pointToMouthLedOn();
    activateControls();

    finishTime = millis() + POINT_TO_MOUTH_WAIT_TIME + MAKE_WITH_WAIT_TIME;
    isStatusActivateGame = true;
  }

  if ((finishTime - MAKE_WITH_WAIT_TIME) <= millis())
  {
    makeAWishLedOn();
  }

  if (finishTime <= millis())
  {
    desactivateControls();
    pushButtonCoinLedOn();

    status = STATUS_WAITING_RELEASE_COIN;
  }

  if (isControlsActive() == true)
  {
    moveControls();
  }

  return status;
}

void statusActivateGame_Reset()
{
  isStatusActivateGame = false;
  desactivateControls();
  makeAWishLedOff();
  pushButtonCoinLedOff();

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
