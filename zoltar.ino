#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Configuration.h"
#include "StatusInit.h"
#include "StatusStandBy.h"
#include "StatusActivateGame.h"
#include "StatusWaittingReleaseCoin.h"
#include "StatusWinOrLost.h"
#include "StatusWin.h"
#include "StatusLost.h"

int status;

void setup() {    
    Serial.begin(BAUDS);
    
    initializePins();

    initializeStatusInit();
    initializeStatusActiveGame();    

    initStatusWin();
    initStatusLost();

    // Set initial status
    status = STATUS_STAND_BY;
} 

void loop() {
  
  printStatus();

  switch (status) {

    case STATUS_INIT:
      status = statusInit(status);
      break;

    case STATUS_ACTIVATE_GAME:
      status = statusActivateGame(status);
      break;

    case STATUS_WAITING_RELEASE_COIN:
      status = statusWaittingReleaseCoin(status);
      break;

    case STATUS_WIN_OR_LOST:
      status = statusWinOrLost(status);
      break;

    case STATUS_WIN:
        status = statusWin(status);
      break;

    case STATUS_LOST:
        status = statusLost(status);
      break;

    case STATUS_OFF:
        // Esperar a que termine la música
        // desactivar musica y luces y movimiento. Todo
        // Activar siguiente estado STATUS_STAND_BY

      break;

    default: //case "STATUS_STAND_BY":
      status = statusStandBy(status);
      break;

  }

  checkContinuousActiveThings();
}

void checkContinuousActiveThings() {
  if (statusInit_headMoveIsActive()) { 
    statusInit_moveHead();
  }
}

// Initialize Modules Methods
void initializeStatusInit() {
  // TODO Activate Music Initalize
  //statusInit_initMusicConfiguration();
  statusInit_initHeadMove();
}

void initializeStatusActiveGame() {
    statusActivateGame_initControlls();
    statusActivateGame_initSoundConfiguration();
}

void initializePins() {
    pinMode(DETECT_COIN_PIN, INPUT);
    pinMode(BACKGROUND_LED_PIN, OUTPUT);
    pinMode(EYES_LED_PIN, OUTPUT);
    pinMode(POINT_TO_MOUTH_LED_PIN, OUTPUT);
    pinMode(PUSH_BUTTON_COIN_LED_PIN, OUTPUT);
    
    //pinMode(CONTROLS_DT_PIN,INPUT);
    //pinMode(CONTROLS_CLK_PIN,INPUT);

    pinMode(SOLENOID_PIN, OUTPUT);
    pinMode(FREE_COIN_BUTTON_PIN, INPUT);
    
    pinMode(MOTOR_WIN_ENABLE_PIN, OUTPUT);
    pinMode(MOTOR_WIN_STEP_PIN, OUTPUT);
    pinMode(MOTOR_WIN_DIR_PIN, OUTPUT);
    pinMode(SWITCH_WIN_CARD_MOTOR_PIN, INPUT);

}

void printStatus() {
  String statusText = "STAND_BY";

  switch (status) {
    
    case STATUS_INIT:
      statusText = "INIT";
    break;
    case STATUS_ACTIVATE_GAME:
      statusText = "ACTIVATE_GAME";
    break;
    case STATUS_WAITING_RELEASE_COIN:
      statusText = "WAITING_RELEASE_COIN";
    break;
    case STATUS_WIN_OR_LOST:
      statusText = "WIN_OR_LOST";
    break;
    case STATUS_WIN:
      statusText = "WIN";
    break;
    case STATUS_LOST:
      statusText = "LOST";
    break;
    case STATUS_OFF:
      statusText = "OFF";
    break;
    default:
      statusText = "STAND_BY";
    break;
  }

  unsigned long timeLoop = millis();
  Serial.println("STATUS :" + statusText + " - " + timeLoop);
}

