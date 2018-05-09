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
#include <Servo.h>
int pos;

DFRobotDFPlayerMini soundDFPlayer;
SoftwareSerial soundSoftwareSerial(SOUND_RX_PIN, SOUND_TX_PIN); // RX, TX

boolean isStatusActivateGame;
unsigned long finishTime;
boolean controlsActive;
//int clkLastSignal, clkLastSignal2;

void statusActivateGame_initSoundConfiguration() {
    // soundSoftwareSerial.begin(BAUDS);
    // if (!soundDFPlayer.begin(soundSoftwareSerial)) {
    //   while(true);
    // }
    
    // soundDFPlayer.volume(SOUND_VOLUME);
}

void pointToMouthLedOn() {  
  digitalWrite(POINT_TO_MOUTH_LED_PIN, HIGH);
}

void playSound() {
  // soundDFPlayer.play(1);
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

boolean isControlsActive() {
  return controlsActive;
}

void moveControls() {
//  int clkSignal = digitalRead(CONTROLS_CLK_PIN);
//  int dtSignal = digitalRead(CONTROLS_DT_PIN);
//
//   int servoMove = servoMotor.read();
//   if (clkSignal != clkLastSignal && clkSignal != clkLastSignal2) {
//    
//     if (dtSignal == HIGH) {
//        //Serial.println("Izquierda");
//        pos = pos + 1;
//        if (pos > 158) {
//          pos = 158;
//        }
//     } else {       
//        //Serial.println("Derecha");
//        pos = pos - 1;
//        if (pos < 0) {
//          pos = 0;
//        }        
//     }
//      
//      
//     Serial.println(pos);
//     servoMotor.write(pos);
//     delay(100);
//
//     clkLastSignal2 = clkLastSignal;
//  }
//
//  clkLastSignal = clkSignal;
}

void statusActivateGame_Reset() {
  isStatusActivateGame = false;
  desactivateControlls();


//  for (int initPoint = 158; initPoint >= 0; initPoint--) {
//    servoMotor.write(initPoint);
//    delay(15);
//  }
//  pos = 0;
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
    
    status = STATUS_WAITING_RELEASE_COIN;
  }

  if (isControlsActive() == true) {
    moveControls();
  }
  
  return status;
}


