/**
 * Servo Variables
 */
#include <Servo.h>

Servo servoMotor;
int servoGrados;
int servoPin = 9;

int DOWN_LIMIT = -1800;
int UP_LIMIT = 1800; // 135
int INCREMENT = 1;

int lastRotatoryValue = 0;
int actualRotatoryValue = 0;

/**
 * Rotatory variables
 */
//these pins can not be changed 2/3 are special pins
int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

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
  
  if (servoMotor.attached() == true) {
    Serial.println("Estamos conectados al servo");
  } else {
    Serial.println("Error de conexión al servo");
  }
  
  //servoMotor.write(servoGrados);
  servoMotor.writeMicroseconds(1400);
  delay(1000);
  int readServo = servoMotor.read();
  
  Serial.println(readServo);
  Serial.println("Ok.");

  // Rotatory
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  
  digitalWrite(encoderPin1, HIGH);
  digitalWrite(encoderPin2, HIGH);
  
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);

}

/**
 * Loop
 */
void loop() {
  actualRotatoryValue = encoderValue / 4;
  
  if (actualRotatoryValue != lastRotatoryValue) {

    if (actualRotatoryValue > lastRotatoryValue) {
      
      Serial.println ("sentido antihorario");
      servoGrados = servoGrados + INCREMENT;
       
      if (servoGrados > UP_LIMIT) {
        servoGrados = UP_LIMIT;
      }

       servoMotor.writeMicroseconds(1500);
       
    } else {
    
      Serial.println("sentido horario");
      servoGrados = servoGrados - INCREMENT;
       
      if (servoGrados < DOWN_LIMIT) {
        servoGrados = DOWN_LIMIT;
      }
      
      servoMotor.writeMicroseconds(1350);
    }

    //Serial.println(servoGrados);
    //servoMotor.write(servoGrados);
    delay(10);
    servoMotor.writeMicroseconds(1400);
    
  }
  
  lastRotatoryValue = actualRotatoryValue;
}

/**
 * Interrupts rotatory
 */
void updateEncoder() {
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
  
  int encoded = (MSB << 1) |LSB;
  
  int sum = (lastEncoded << 2) | encoded;
  
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
  lastEncoded = encoded;
}

