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

int status;

void setup()
{
  Serial.println("00000000");
  Serial.begin(BAUDS);

  Serial.println("1");
  initializePins();
  Serial.println("2");
  statusInit_StandBy();
  Serial.println("3");
  statusInit_initialize();
  Serial.println("4");
  statusActivateGame_init();
  Serial.println("5");
  statusWaittingReleaseCoin_Reset();
  Serial.println("6");
  statusWinOrLost_Reset();
  Serial.println("7");

  // Set initial status
  status = STATUS_STAND_BY;
}

void initializePins()
{
  pinMode(DETECT_COIN_PIN, INPUT);
  pinMode(ENABLE_COIN_MACHINE_PIN, OUTPUT);

  pinMode(EYES_LED_PIN, OUTPUT);
  pinMode(POINT_TO_MOUTH_LED_PIN, OUTPUT);
  pinMode(PUSH_BUTTON_COIN_LED_PIN, OUTPUT);
  pinMode(MAKE_WISH_LED_PIN, OUTPUT);

  pinMode(CONTROLS_VERTICAL_DT_PIN, INPUT);
  pinMode(CONTROLS_VERTICAL_CLK_PIN, INPUT);
  pinMode(CONTROLS_HORIZONTAL_DT_PIN, INPUT);
  pinMode(CONTROLS_HORIZONTAL_CLK_PIN, INPUT);

  pinMode(SOLENOID_PIN, OUTPUT);
  pinMode(FREE_COIN_BUTTON_PIN, INPUT);
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
    break;

  case STATUS_LOST:
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
    delay(100);
  }
}

void printStatus()
{
  String statusText;

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

  default:
    statusText = "STAND_BY";
    break;
  }

  unsigned long timeLoop = millis();
  Serial.println("STATUS :" + statusText + " - " + timeLoop);
}
