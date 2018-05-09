#include <Servo.h>

Servo servoMotor;
int servoGrados;

int pinA = 22;  // Connected to CLK on KY-040
int pinB = 23;  // Connected to DT on KY-040
int servoPin = 9;
int encoderPosCount = 0; 
int last;  
int actual;

int DOWN_LIMIT = 0;
int UP_LIMIT = 180;
int INCREMENT = 1;

void setup() {
   servoGrados = 90;
  
   pinMode(pinA,INPUT);
   pinMode(pinB,INPUT);

   servoMotor.attach(servoPin);
   servoMotor.write(servoGrados);
   delay(1000);

   /* Read Pin A
   Whatever state it's in will reflect the last position   
   */
   actual = digitalRead(pinA);   
   Serial.begin (9600);
} 

void loop() { 
   actual = digitalRead(pinA);
   
   if (actual != last) {
     
     if (digitalRead(pinB) != actual) {
       encoderPosCount ++;
       
       //Serial.println ("sentido antihorario");
       servoGrados = servoGrados + INCREMENT;
       
       if (servoGrados > UP_LIMIT) {
        servoGrados = UP_LIMIT;
       }
       
     } else {
       encoderPosCount--;

       //Serial.println("sentido horario");
       servoGrados = servoGrados - INCREMENT;
       
       if (servoGrados < DOWN_LIMIT) {
        servoGrados = DOWN_LIMIT;
       }
     }     
     
     servoMotor.write(servoGrados);

     Serial.print("Encoder Position: ");
     Serial.println(encoderPosCount);
     delay(10);
   }
   
   last = actual;
}
