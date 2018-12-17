#include <Servo.h>

Servo servoMotor;

int pinA = 23;  // Connected to CLK on KY-040
int pinB = 22;  // Connected to DT on KY-040
int pinALast, pinBLast;
boolean bCW;


void setup() {
 pinMode (pinA,INPUT);
 pinMode (pinB,INPUT);

 servoMotor.attach(9);
 servoMotor.writeMicroseconds(1500);

 /* Read Pin A
 Whatever state it's in will reflect the last position   
 */
 pinALast = digitalRead(pinA); 
 pinBLast = pinALast;  
 Serial.begin (9600);
} 

void loop() { 
  int aVal = digitalRead(pinA);
  int valoRPinB = digitalRead(pinB);
   
   if (aVal != pinALast && aVal != pinBLast) {
    
     if (valoRPinB == HIGH) {
       Serial.println ("sentido antihorario");
       servoMotor.writeMicroseconds(1600);
       
     } else {
       Serial.println("sentido horario");
       servoMotor.writeMicroseconds(1250);
     }

     delay(100);
     servoMotor.writeMicroseconds(1500);
}

  pinALast = aVal;
} 
