#include "Arduino.h"
#include "Servo.h"
#include "Configuration.h"

int status;

Servo headServoMotor;
int servoHeadPosition;
int servoDirection;
unsigned long finishTime;
boolean runningGame;

void resetGame()
{
  while (servoHeadPosition < INIT_HEAD_SERVO_POSITION)
  {
    servoHeadPosition++;
    headServoMotor.write(servoHeadPosition);
    delay(100);
  }

  servoHeadPosition = INIT_HEAD_SERVO_POSITION;
  servoDirection = -STEP_HEAD_SERVO_POSITION;

  digitalWrite(EYES_LED_PIN, LOW);

  Serial.println("Stop game.");
  runningGame = false;
}

void setup()
{
  delay(2000);
  Serial.println("Init nano...");
  Serial.begin(BAUDS);

  Serial.println("initialize Pins...");
  pinMode(EYES_LED_PIN, OUTPUT);

  Serial.println("Init Head Servo...");
  pinMode(HEAD_SERVO_PIN, OUTPUT);
  headServoMotor.attach(HEAD_SERVO_PIN);

  pinMode(ON_PIN, INPUT_PULLUP);

  runningGame = false;
  servoHeadPosition = INIT_HEAD_SERVO_POSITION;
  servoDirection = -STEP_HEAD_SERVO_POSITION
}

void initGame()
{
  runningGame = true;

  Serial.println("Eyes leds on...");
  digitalWrite(EYES_LED_PIN, HIGH);

  finishTime = millis() + GAME_TIME;
}

void checkRunGame()
{
  if (!runningGame)
  {
    int activateSignal = digitalRead(ON_PIN);
    if (activateSignal == HIGH)
    {
      initGame();
    }
  }
}

void loop()
{
  checkRunGame();
  if (runningGame)
  {
    if (finishTime > millis())
    {
      moveHead();
    }
    else
    {
      resetGame();
    }
  }
}

void moveHead()
{
  servoHeadPosition = servoHeadPosition + servoDirection;

  if (servoHeadPosition > INIT_HEAD_SERVO_POSITION)
  {
    servoHeadPosition = INIT_HEAD_SERVO_POSITION;
    servoDirection = -STEP_HEAD_SERVO_POSITION;
  }

  if (servoHeadPosition < MAX_HEAD_SERVO_POSITION)
  {
    servoHeadPosition = MAX_HEAD_SERVO_POSITION;
    servoDirection = STEP_HEAD_SERVO_POSITION;
  }

  headServoMotor.write(servoHeadPosition);

  delay(100);
}
