#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Servo.h"
#include "Configuration.h"
#include "StatusStandBy.h"
#include "StatusInit.h"
#include "StatusActivateGame.h"

int status;

void setup()
{
  Serial.println("00000000");
  Serial.begin(BAUDS);

  Serial.println("Initialize pins");
  initializePins();
  Serial.println("init Stand By...");
  statusInit_StandBy();
  Serial.println("Init music configuration");
  initMusicConfiguration();
  Serial.println("Init Activate Game");
  statusActivateGame_init();
  Serial.println("INIT GAME...");

  // Set initial status
  status = STATUS_STAND_BY;
}

void initializePins()
{
  pinMode(DETECT_COIN_PIN, INPUT);
  pinMode(ENABLE_COIN_MACHINE_PIN, OUTPUT);

  pinMode(POINT_TO_MOUTH_LED_PIN, OUTPUT);
  pinMode(PUSH_BUTTON_COIN_LED_PIN, OUTPUT);
  pinMode(MAKE_WISH_LED_PIN, OUTPUT);

  pinMode(NANO_PIN, OUTPUT);

  pinMode(CONTROLS_VERTICAL_DT_PIN, INPUT_PULLUP);
  pinMode(CONTROLS_VERTICAL_CLK_PIN, INPUT_PULLUP);
  pinMode(CONTROLS_HORIZONTAL_DT_PIN, INPUT_PULLUP);
  pinMode(CONTROLS_HORIZONTAL_CLK_PIN, INPUT_PULLUP);

  pinMode(SOLENOID_PIN, OUTPUT);
}

void loop()
{

  //printStatus();

  switch (status)
  {
  case STATUS_INIT:
    status = statusInit(status);
    break;

  case STATUS_ACTIVATE_GAME:
    status = statusActivateGame(status);
    break;

  case STATUS_WAITING_RELEASE_COIN:
    nano_Off();
    status = STATUS_STAND_BY;
    break;

  default: //case "STATUS_STAND_BY":
    status = statusStandBy(status);
    break;
  }
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

  default:
    statusText = "STAND_BY";
    break;
  }

  unsigned long timeLoop = millis();
  Serial.println("STATUS :" + statusText + " - " + timeLoop);
}
