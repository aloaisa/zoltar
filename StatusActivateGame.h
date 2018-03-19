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
boolean isStatusActivateGame = false;
SoftwareSerial soundSoftwareSerial(SOUND_RX_PIN, SOUND_TX_PIN); // RX, TX
unsigned long finishTime;
boolean controlsActive;
int clkLastSignal, clkLastSignal2;


void initSoundConfiguration() {
    soundSoftwareSerial.begin(BAUDS);
    if (!soundDFPlayer.begin(soundSoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      while(true);
    }
    
    soundDFPlayer.volume(SOUND_VOLUME);
}

void initControlls() {
  controlsActive = false;
  clkLastSignal = digitalRead(CONTROLS_CLK_PIN);
  clkLastSignal2 = clkLastSignal;
}

void pointToMouthLedOn() {  
  digitalWrite(POINT_TO_MOUTH_LED_PIN, HIGH);
}

void playSound() {
  soundDFPlayer.play(1);
}

void pushButtonCoinLedOn() {
  digitalWrite(PUSH_BUTTON_COIN_LED_PIN, HIGH); // "Push coin button" Leds on
}

void activateControlls() {
   controlsActive = true;
}

void desactivateControlls() {
  controlsActive = false;
  
}

void moveControls() {
  int clkSignal = digitalRead(CONTROLS_CLK_PIN);
  int dtSignal = digitalRead(CONTROLS_DT_PIN);
   
   if (clkSignal != clkLastSignal && clkSignal != clkLastSignal2) {
    
     if (dtSignal == HIGH) {
       Serial.println("Izquierda");
       
     } else {
       Serial.println("Derecha");
       
     }     

     clkLastSignal2 = clkLastSignal;
  }

  clkLastSignal = clkSignal;
}

int statusActivateGame(int status) { 
  if (isStatusActivateGame == false) {
    pointToMouthLedOn();
    playSound();
    activateControlls();

    finishTime = millis() + POINT_TO_MOUTH_WAIT_TIME;
    isStatusActivateGame = true;
  }
  
  if (finishTime < millis()) {
    desactivateControlls();
    pushButtonCoinLedOn();
    
    //status = STATUS_WAITING_RELEASE_COIN;
  }

  if (controlsActive == true) {
    moveControls();
  }
  
  return status;
}


