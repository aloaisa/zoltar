
#include <AccelStepper.h>

// for the Arduino Uno + CNC shield V3 + A4988 + FL42STH47-1684A

#define MOTOR_X_ENABLE_PIN 8
#define MOTOR_X_STEP_PIN 2
#define MOTOR_X_DIR_PIN 5

AccelStepper motor_X(1, MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN); 


void setup()
{
  motor_X.setEnablePin(MOTOR_X_ENABLE_PIN);
  motor_X.setPinsInverted(false, false, true);
  motor_X.setAcceleration(20);  
  motor_X.move(200);
  motor_X.setMaxSpeed(100);
  //motor_X.setSpeed(100);
  motor_X.enableOutputs();
}

void loop()
{
  motor_X.run();
}
