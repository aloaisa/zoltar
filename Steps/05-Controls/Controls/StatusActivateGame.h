/**

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

int verticalPos, horizontalPos;

int incrementoVertical = 0;
int incrementoHorizontal = 0;

void initSoundConfiguration() {
  Serial.println("Init sound configuration...");

  soundSoftwareSerial.begin(BAUDS);
  if (!soundDFPlayer.begin(soundSoftwareSerial))
  {
    while (true)
      ;
  }

  soundDFPlayer.volume(SOUND_VOLUME);
}

void freeCoin() {
  Serial.println("Free selenoid coin ...");
  digitalWrite(SOLENOID_PIN, HIGH);
  delay(500);
  digitalWrite(SOLENOID_PIN, LOW);
  delay(500);

  digitalWrite(SOLENOID_PIN, HIGH);
  delay(500);
  digitalWrite(SOLENOID_PIN, LOW);
  delay(500);

  digitalWrite(SOLENOID_PIN, HIGH);
  delay(500);
  digitalWrite(SOLENOID_PIN, LOW);
  delay(500);
}

void initServoConfiguration() {
  Serial.println("Init control servos configuration...");

  verticalServo.attach(SERVO_VERTICAL_PIN);
  verticalServo.write(MAX_SERVO_VERTICAL_POSITION); // reset position
  delay(1000);

  freeCoin();

  verticalServo.write(INIT_SERVO_VERTICAL_POSITION); // 0 position
  delay(1000);

  horizontalServo.attach(SERVO_HORIZONTAL_PIN);
  horizontalServo.write(INIT_SERVO_HORIZONTAL_POSITION); // 0 position
  delay(1000);
}

void statusActivateGame_init() {
  initSoundConfiguration();
  initServoConfiguration();
}

void pointToMouthLedOn() {
  Serial.println("pointToMouthLedOn");
  digitalWrite(POINT_TO_MOUTH_LED_PIN, HIGH);
}

void makeAWishLedOn() {
  if (isWishLedOn == false)
  {
    Serial.println("makeAWishLedOn");
    isWishLedOn = true;
    digitalWrite(MAKE_WISH_LED_PIN, HIGH);
  }
}

void pushButtonCoinLedOn()
{
  Serial.println("pushButtonCoinLedOn");
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, HIGH);
}

void playSound()
{
  soundDFPlayer.play(1);
}

void activateControls()
{
  verticalPos = INIT_SERVO_VERTICAL_POSITION;
  horizontalPos = INIT_SERVO_HORIZONTAL_POSITION;

  attachInterrupt(digitalPinToInterrupt(CONTROLS_VERTICAL_DT_PIN), verticalServoInterruptionDT, RISING);
  attachInterrupt(digitalPinToInterrupt(CONTROLS_VERTICAL_CLK_PIN), verticalServoInterruptionCLK, RISING);
  attachInterrupt(digitalPinToInterrupt(CONTROLS_HORIZONTAL_DT_PIN), horizontalServoInterruptionDT, RISING);
  attachInterrupt(digitalPinToInterrupt(CONTROLS_HORIZONTAL_CLK_PIN), horizontalServoInterruptionCLK, RISING);
}

void desactivateControls()
{
  detachInterrupt(digitalPinToInterrupt(CONTROLS_VERTICAL_DT_PIN));
  detachInterrupt(digitalPinToInterrupt(CONTROLS_VERTICAL_CLK_PIN));
  detachInterrupt(digitalPinToInterrupt(CONTROLS_HORIZONTAL_DT_PIN));
  detachInterrupt(digitalPinToInterrupt(CONTROLS_HORIZONTAL_CLK_PIN));
}

int statusActivateGame(int status)
{
  if (isStatusActivateGame == false)
  {
    Serial.println("STATUS_ACTIVATE_GAME...");
    Serial.println("Play Sound...");
    playSound();
    Serial.println("Point to mouth led ON...");
    pointToMouthLedOn();
    Serial.println("Activate control...");
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

  return status;
}

void verticalServoInterruptionDT() {
  if (digitalRead(CONTROLS_VERTICAL_DT_PIN) == LOW) {
    moveVerticalServo(1);
  } else {
    moveVerticalServo(-1);
  }
}

void verticalServoInterruptionCLK() {
  if (digitalRead(CONTROLS_VERTICAL_CLK_PIN) == LOW) {
    moveVerticalServo(-1);
  } else {
    moveVerticalServo(1);
  }
}

void horizontalServoInterruptionDT()
{
  if (digitalRead(CONTROLS_HORIZONTAL_DT_PIN) == LOW) {
    moveVerticalServo(1);
  } else {
    moveVerticalServo(-1);
  }
}

void horizontalServoInterruptionCLK()
{
  if (digitalRead(CONTROLS_HORIZONTAL_CLK_PIN) == LOW) {
    moveVerticalServo(-1);
  } else {
    moveVerticalServo(1);
  }
}

void moveVerticalServo(int step) {

  verticalPos += step;
  if (verticalPos > MAX_SERVO_VERTICAL_POSITION)
  {
    verticalPos = MAX_SERVO_VERTICAL_POSITION;
  }

  if (verticalPos < INIT_SERVO_VERTICAL_POSITION)
  {
    verticalPos = INIT_SERVO_VERTICAL_POSITION;
  }

  verticalServo.write(verticalPos);
}
