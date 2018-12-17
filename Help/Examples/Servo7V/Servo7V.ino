/**
 * Servo Variables
 */
#include <Servo.h>

Servo servoMotor;
int servoGrados;
int servoPin = 8;

/**
 * Setup
 */
void setup() {
  Serial.begin (9600);

  // Servo
  servoGrados = 0;

  Serial.println("Init Servo...");
  Serial.println(servoGrados);
  
  servoMotor.attach(servoPin);
  servoMotor.write(servoGrados);
  delay(1000);
  
  int readServo = servoMotor.read();
  Serial.println(readServo);
  Serial.println("Ok.");

}

/**
 * Loop
 */
void loop() {

    for (int cont = 0; cont < 180; cont++) {
        Serial.println(cont);
        servoMotor.write(cont);
        delay(1000);
    }

    for (int cont = 180; cont > 0; cont--) {
      Serial.println(cont);
        servoMotor.write(cont);
        delay(1000);
    }
}
