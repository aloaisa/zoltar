#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Servo.h"
#include "Configuration.h"
#include "StatusStandBy.h"
#include "StatusInit.h"
#include "StatusActivateGame.h"
#include "StatusWaittingReleaseCoin.h"
#include "StatusWinOrLost.h"
#include "StatusWin.h"
#include "StatusLost.h"

int status;

void setup() {
  Serial.begin(BAUDS);

  Serial.println("Initialize pins");
  initializePins();

  Serial.println("init Stand By...");
  statusInit_StandBy();

  Serial.println("Init music configuration");
  initMusicConfiguration();

  Serial.println("Init Activate Game");
  statusActivateGame_init();

  Serial.println("Init Waiting release coin");
  statusWaittingReleaseCoin_Reset();

  Serial.println("Init Win or lost");
  statusWinOrLost_Reset();

  Serial.println("Init Win");
  initStatusWin();

  Serial.println("Init Win");
  initStatusLost();

  Serial.println("INIT GAME...");
  Serial.println("Insert coin: ");

  // Set initial status
  status = STATUS_STAND_BY;

  playStartZoltarSound();
}

void initializePins() {
  pinMode(DETECT_COIN_PIN, INPUT_PULLUP);
  pinMode(ENABLE_COIN_MACHINE_PIN, OUTPUT);

  pinMode(POINT_TO_MOUTH_LED_PIN, OUTPUT);
  pinMode(PUSH_BUTTON_COIN_LED_PIN, OUTPUT);
  pinMode(MAKE_WISH_LED_PIN, OUTPUT);

  pinMode(NANO_PIN, OUTPUT);

  pinMode(CONTROLS_VERTICAL_DT_PIN, INPUT);
  pinMode(CONTROLS_VERTICAL_CLK_PIN, INPUT);
  pinMode(CONTROLS_HORIZONTAL_DT_PIN, INPUT);
  pinMode(CONTROLS_HORIZONTAL_CLK_PIN, INPUT);

  pinMode(SOLENOID_PIN, OUTPUT);

  pinMode(FREE_COIN_BUTTON_PIN, INPUT_PULLUP);

  pinMode(MOTOR_ENABLE_PIN, OUTPUT);

  pinMode(MOTOR_WIN_STEP_PIN, OUTPUT);
  pinMode(MOTOR_WIN_DIR_PIN, OUTPUT);
  pinMode(SWITCH_WIN_CARD_MOTOR_PIN, INPUT);

  pinMode(MOTOR_LOST_STEP_PIN, OUTPUT);
  pinMode(MOTOR_LOST_DIR_PIN, OUTPUT);
  pinMode(SWITCH_LOST_CARD_MOTOR_PIN, INPUT);
}

int statusOff(int status) {
  nano_Off();

  statusInit_StandBy();
  statusInit_Reset();
  statusActivateGame_Reset();
  statusWaittingReleaseCoin_Reset();
  statusWinOrLost_Reset();

  status = STATUS_STAND_BY;

  Serial.println("Insert coin: ");

  return status;
}

void loop() {

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
    status = statusOff(status);
    break;

  default: //case "STATUS_STAND_BY":
    status = statusStandBy(status);
    break;
  }
}
