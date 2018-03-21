/**
 * Init status:
 * only run one time per game.
 * Play background music - 2 Digital-analogical inputs
 * On background leds - 1 digital input
 * On eyes leds - 1 digital input
 * On mouth move - 1 digital input
 * And wait a defined time to start the game
 */
#include <Stepper.h>

boolean isStatusInit = false;

Stepper stepperHeadMove(STEPS, MOTOR_1_IN1_PIN, MOTOR_1_IN2_PIN, MOTOR_1_IN3_PIN, MOTOR_1_IN4_PIN);
boolean mouthMove;

DFRobotDFPlayerMini musicDFPlayer;
SoftwareSerial musicSoftwareSerial(MUSIC_RX_PIN, MUSIC_TX_PIN); // RX, TX

void initMusicConfiguration() {
    musicSoftwareSerial.begin(BAUDS);
    if (!musicDFPlayer.begin(musicSoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
      while(true);
    }
    
    musicDFPlayer.volume(MUSIC_VOLUME);
}

void initHeadMove() {
  mouthMove = false;
  stepperHeadMove.setSpeed(20); // 0 to 20
}

void playMusic() {
  musicDFPlayer.play(1);  //Play the first mp3
}

void backgroundLedOn() {  
  digitalWrite(BACKGROUND_LED_PIN, HIGH);
}

void eyesLedOn() {
  digitalWrite(EYES_LED_PIN, HIGH);
}

void mouthMoveOn() {
  mouthMove = true;
}

boolean headMoveIsActive() {
  return mouthMove;
}

void moveHead() {
  stepperHeadMove.step(10); // 1 to 10
}

int statusInit(int status) {
  if (isStatusInit == false) {
    playMusic();
    backgroundLedOn();
    eyesLedOn();
    mouthMoveOn();
    
    isStatusInit = true;
  
    status = STATUS_ACTIVATE_GAME;
  }

  return status;
}

