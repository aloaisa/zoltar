#include <Servo.h>

Servo servoMotor;
int servoGrados;

int pinA = 32;  // Connected to CLK on KY-040
 int pinB = 33;  // Connected to DT on KY-040
 int encoderPosCount = 0; 
 int pinALast;  
 int aVal;
 boolean bCW;


 void setup() {
   servoGrados = 90;
  
   pinMode (pinA,INPUT);
   pinMode (pinB,INPUT);

   servoMotor.attach(9);
   servoMotor.write(servoGrados);

   /* Read Pin A
   Whatever state it's in will reflect the last position   
   */
   pinALast = digitalRead(pinA);   
   Serial.begin (9600);
 } 

 void loop() { 
   aVal = digitalRead(pinA);
   if (aVal != pinALast){ // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       encoderPosCount--;
     }
     Serial.print ("Rotated: ");
     if (bCW){
       Serial.println ("sentido antihorario");
       servoGrados = servoGrados + 5;
       if (servoGrados > 135) {
        servoGrados = 135;
       }
     }else{
       Serial.println("sentido horario");
       servoGrados = servoGrados - 5;
       if (servoGrados < 45) {
        servoGrados = 45;
       }
     }
     servoMotor.write(servoGrados);
     Serial.print("Encoder Position: ");
     Serial.println(encoderPosCount);
     
   } 
   pinALast = aVal;
 } 
