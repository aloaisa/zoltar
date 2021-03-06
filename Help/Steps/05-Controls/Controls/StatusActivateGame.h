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

boolean controlsActive;
int verticalPos, horizontalPos;
int lastVerticalPos, lastHorizontalPos;
boolean verticalALast;
boolean verticalBLast;
boolean horizontalALast;
boolean horizontalBLast;
boolean goStopVertical;
boolean goStopHorizontal;

int incrementoVertical = 0;
int incrementoHorizontal = 0;

void initSoundConfiguration() {
  Serial.println("Init sound configuration...");

  soundSoftwareSerial.begin(BAUDS);
  if (!soundDFPlayer.begin(soundSoftwareSerial)) {
    while (true)
      ;
  }

  soundDFPlayer.volume(SOUND_VOLUME);
}

void initServoConfiguration() {
  Serial.println("Init control servos configuration...");

  verticalServo.attach(SERVO_VERTICAL_PIN);
  verticalServo.write(MAX_SERVO_VERTICAL_POSITION); // reset position
  delay(1000);

  digitalWrite(SOLENOID_PIN, HIGH);
  delay(500);
  digitalWrite(SOLENOID_PIN, LOW);
  delay(500);
  
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

void pointToMouthLedOff() {
  digitalWrite(POINT_TO_MOUTH_LED_PIN, LOW);
}

void makeAWishLedOn() {
  if (isWishLedOn == false)
  {
    Serial.println("makeAWishLedOn");
    isWishLedOn = true;
    digitalWrite(MAKE_WISH_LED_PIN, HIGH);

    soundDFPlayer.play(2);
  }
}

void makeAWishLedOff() {
  digitalWrite(MAKE_WISH_LED_PIN, LOW);
  isWishLedOn = false;
}

void pushButtonCoinLedOn() {
  Serial.println("pushButtonCoinLedOn");
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, HIGH);

  soundDFPlayer.play(3);
}

void pushButtonCoinLedOff() {
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, LOW);
}

void playSound() {
  soundDFPlayer.play(1);
}


void activateControls() {
  verticalPos = INIT_SERVO_VERTICAL_POSITION;
  horizontalPos = INIT_SERVO_HORIZONTAL_POSITION;

  lastVerticalPos = 0;
  lastHorizontalPos = 0;

  goStopVertical = 0;
  goStopHorizontal = 0;

  verticalALast = 0;
  verticalBLast = 0;

  horizontalALast = 0;
  horizontalBLast = 0;

  controlsActive = true;
}

void moveVerticalControl() {
  boolean verticalA = digitalRead(CONTROLS_VERTICAL_DT_PIN);
  boolean verticalB = digitalRead(CONTROLS_VERTICAL_CLK_PIN);

  if (goStopVertical == 0) {
    goStopVertical = 1;
  } else {

    if (verticalALast == verticalA && verticalBLast == verticalB) {
      //Serial.println("v");
    } else {

      int nextStep = 0;
      if (verticalALast == 0 && verticalBLast == 0) {
        if (verticalA == 1 && verticalB == 0) {
          nextStep++;
        } else if (verticalA == 0 && verticalB == 1) {
          nextStep--;
        }
      } else if (verticalALast == 1 && verticalBLast == 0) {
        if (verticalA == 1 && verticalB == 1) {
          nextStep++;
        } else if (verticalA == 0 && verticalB == 0) {
          nextStep--;
        }
      } else if (verticalALast == 1 && verticalBLast == 1) {
        if (verticalA == 0 && verticalB == 1) {
          nextStep++;
        } else if (verticalA == 1 && verticalB == 0) {
          nextStep--;
        }
      } else if (verticalALast == 0 && verticalBLast == 1) {
        if (verticalA == 0 && verticalB == 0) {
          nextStep++;
        } else if (verticalA == 1 && verticalB == 1) {
          nextStep--;
        }
      }

      if (nextStep != 0) {
        if (lastVerticalPos != nextStep) {
          lastVerticalPos = nextStep;
        } else {
          verticalPos = verticalPos + nextStep;
          // Serial.print("verticalPos: ");
          // Serial.println(verticalPos);
          goStopVertical = 0;
        }
      }

      if (verticalPos > MAX_SERVO_VERTICAL_POSITION) {
        verticalPos = MAX_SERVO_VERTICAL_POSITION;
      }

      if (verticalPos < INIT_SERVO_VERTICAL_POSITION) {
        verticalPos = INIT_SERVO_VERTICAL_POSITION;
      }

      verticalServo.write(verticalPos);
      delay(15);
    }
  }

  verticalALast = verticalA;
  verticalBLast = verticalB;
}

void moveHorizonalControl() {
  boolean horizontalA = digitalRead(CONTROLS_HORIZONTAL_DT_PIN);
  boolean horizontalB = digitalRead(CONTROLS_HORIZONTAL_CLK_PIN);

  if (goStopHorizontal == 0) {
    goStopHorizontal = 1;
  } else {

    if (horizontalALast == horizontalA && horizontalBLast == horizontalB) {
      // Serial.println("h");
    } else {

      int nextStep = 0;

      if (horizontalALast == 0 && horizontalBLast == 0) {
        if (horizontalA == 1 && horizontalB == 0) {
          nextStep++;
        } else if (horizontalA == 0 && horizontalB == 1) {
          nextStep--;
        }
      } else if (horizontalALast == 1 && horizontalBLast == 0) {
        if (horizontalA == 1 && horizontalB == 1) {
          nextStep++;
        } else if (horizontalA == 0 && horizontalB == 0) {
          nextStep--;
        }
      } else if (horizontalALast == 1 && horizontalBLast == 1) {
        if (horizontalA == 0 && horizontalB == 1) {
          nextStep++;
        } else if (horizontalA == 1 && horizontalB == 0) {
          nextStep--;
        }
      } else if (horizontalALast == 0 && horizontalBLast == 1) {
        if (horizontalA == 0 && horizontalB == 0) {
          nextStep++;
        } else if (horizontalA == 1 && horizontalB == 1) {
          nextStep--;
        }
      }

      if (nextStep != 0) {
        if (lastHorizontalPos != nextStep) {
          lastHorizontalPos = nextStep;
        } else {
          horizontalPos = horizontalPos + nextStep;
          // Serial.print("horizontalPos: ");
          // Serial.println(horizontalPos);
          goStopHorizontal = 0;
        }
      }

      if (horizontalPos > MAX_SERVO_HORIZONTAL_POSITION) {
        horizontalPos = MAX_SERVO_HORIZONTAL_POSITION;
      }

      if (horizontalPos < INIT_SERVO_HORIZONTAL_POSITION) {
        horizontalPos = INIT_SERVO_HORIZONTAL_POSITION;
      }

      horizontalServo.write(horizontalPos);
      delay(15);
    }
  }

  horizontalALast = horizontalA;
  horizontalBLast = horizontalB;
}

void moveControls() {
  moveVerticalControl();
  moveHorizonalControl();
}

int statusActivateGame(int status) {
  
  if (isStatusActivateGame == false) {
    Serial.println("STATUS_ACTIVATE_GAME...");
    Serial.println("Point to mouth led ON...");
    pointToMouthLedOn();
    
    Serial.println("Play Sound...");
    playSound();
    
    Serial.println("Activate controll...");
    activateControls();

    finishTime = millis() + POINT_TO_MOUTH_WAIT_TIME + MAKE_WITH_WAIT_TIME;
    isStatusActivateGame = true;
  }

  if ((finishTime - MAKE_WITH_WAIT_TIME) <= millis()) {
    makeAWishLedOn();
  }

  if (finishTime <= millis()) {
    pushButtonCoinLedOn();
    controlsActive = false;
    status = STATUS_WAITING_RELEASE_COIN;
  }

  if (controlsActive == true) {
    moveControls();
  }

  return status;
}

void statusActivateGame_Reset()
{
  isStatusActivateGame = false;
  makeAWishLedOff();
  pushButtonCoinLedOff();
  pointToMouthLedOff();

  // Move servos to 0 position
  initServoConfiguration();
}
