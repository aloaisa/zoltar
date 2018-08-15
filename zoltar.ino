#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>
#include "Configuration.h"
#include "StatusInit.h"
#include "StatusStandBy.h"
#include "StatusActivateGame.h"
#include "StatusWaittingReleaseCoin.h"
#include "StatusWinOrLost.h"
#include "StatusWin.h"
#include "StatusLost.h"

int status;

void setup()
{
  Serial.begin(BAUDS);

  initializePins();

  statusInit_initialize();
  statusActivateGame_init();
  statusWaittingReleaseCoin_Reset();
  statusWinOrLost_Reset();

  initStatusWin();
  initStatusLost();

  // Set initial status
  status = STATUS_STAND_BY;
}

void initializePins()
{
  pinMode(DETECT_COIN_PIN, INPUT);
  pinMode(EYES_LED_PIN, OUTPUT);
  pinMode(POINT_TO_MOUTH_LED_PIN, OUTPUT);
  pinMode(PUSH_BUTTON_COIN_LED_PIN, OUTPUT);

  pinMode(CONTROLS_VERTICAL_DT_PIN, INPUT);
  pinMode(CONTROLS_VERTICAL_CLK_PIN, INPUT);
  pinMode(CONTROLS_HORIZONTAL_DT_PIN, INPUT);
  pinMode(CONTROLS_HORIZONTAL_CLK_PIN, INPUT);

  pinMode(SOLENOID_PIN, OUTPUT);
  pinMode(FREE_COIN_BUTTON_PIN, INPUT);

  pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_WIN_STEP_PIN, OUTPUT);
  pinMode(MOTOR_WIN_DIR_PIN, OUTPUT);
  pinMode(SWITCH_WIN_CARD_MOTOR_PIN, INPUT);
}

void loop()
{

  printStatus();

  switch (status)
  {

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

  checkContinuousActiveThings();
}

void checkContinuousActiveThings()
{
  if (statusInit_headMoveIsActive())
  {
    statusInit_moveHead();
  }
}

int statusOff(int status)
{
  statusInit_Reset();
  statusActivateGame_Reset();
  statusWaittingReleaseCoin_Reset();
  statusWinOrLost_Reset();

  status = STATUS_STAND_BY;
  return status;
}

void printStatus()
{
  String statusText = "STAND_BY";

  switch (status)
  {

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
