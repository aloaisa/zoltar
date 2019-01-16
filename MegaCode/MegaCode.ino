#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Servo.h"
#include "Configuration.h"
#include "StatusStandBy.h"
#include "StatusActivateGame.h"
#include "StatusInit.h"
#include "StatusWaittingReleaseCoin.h"
#include "StatusWinOrLost.h"
#include "StatusWin.h"
#include "StatusLost.h"

int status;
unsigned long off_nano_time;

void setup() {
  Serial.begin(BAUDS);

  Serial.println("Initialize pins");
  initializePins();

  Serial.println("init Stand By...");
  nano_Off();

  Serial.println("Reset Init status...");
  statusInit_Reset();

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
  digitalWrite(ENABLE_COIN_MACHINE_PIN, HIGH);
  
  Serial.println("Insert coin: ");

  // Set initial status
  status = STATUS_STAND_BY;

  playStartZoltarSound();
}

void initializePins() {
  pinMode(DETECT_COIN_PIN, INPUT_PULLUP);
  pinMode(ENABLE_COIN_MACHINE_PIN, OUTPUT);

  digitalWrite(RESET_PIN, HIGH);
  pinMode(RESET_PIN, OUTPUT);

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

  pinMode(SENSOR_WIN_PIN, INPUT_PULLUP);

  pinMode(MOTOR_ENABLE_PIN, OUTPUT);

  pinMode(MOTOR_WIN_STEP_PIN, OUTPUT);
  pinMode(MOTOR_WIN_DIR_PIN, OUTPUT);
  pinMode(SWITCH_WIN_CARD_MOTOR_PIN, INPUT);

  pinMode(MOTOR_LOST_STEP_PIN, OUTPUT);
  pinMode(MOTOR_LOST_DIR_PIN, OUTPUT);
  pinMode(SWITCH_LOST_CARD_MOTOR_PIN, INPUT);

  pinMode(SWITCH_NEED_CARDS_LOST_CARD_MOTOR_PIN, INPUT_PULLUP);
}

boolean isLastCardsSwitchActivate() {
  boolean result = false;

  int lostCards = digitalRead(SWITCH_NEED_CARDS_LOST_CARD_MOTOR_PIN);
  if (lostCards == HIGH) {
    result = true;
  }

  return result;
}

void statusOff(int status) {

  digitalWrite(ENABLE_COIN_MACHINE_PIN, LOW);

  // WAIT UNTIL MUSIC FINISH
  Serial.print("off_nano_time: ");
  Serial.println(off_nano_time);

  while (off_nano_time > millis()) {
    Serial.print("millis(): ");
    Serial.println(millis());
    delay(500);
  }

  nano_Off();

  statusInit_Reset();
  statusActivateGame_Reset();
  statusWaittingReleaseCoin_Reset();
  statusWinOrLost_Reset();
  initStatusWin();
  initStatusLost();

  if (isLastCardsSwitchActivate() == true) {
    Serial.println("isLastCardsSwitchActivate: true");
    playRefillCardSound();
    delay(2000);
  } else {
    Serial.println("isLastCardsSwitchActivate: false");
  }

  digitalWrite(RESET_PIN, LOW);
}

void loop() {

  switch (status) {
  case STATUS_INIT:
    status = statusInit(status);

    if (status == STATUS_ACTIVATE_GAME) {
      off_nano_time = millis() + TOTAL_MUSIC_TIME;
      Serial.print("off_nano_time: ");
      Serial.println(off_nano_time);
      Serial.print("millis(): ");
      Serial.println(millis());
    }
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
    statusOff(status);
    break;

  default: //case "STATUS_STAND_BY":
    status = statusStandBy(status);
    break;
  }
}
