const int encoderPinA= 25;
const int encoderPinB= 26;

boolean ALast = 0;
boolean BLast = 0;
boolean goStop = 0;

int lastMovement = 0;

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);

  ALast = 0;
  BLast = 0;

  Serial.begin(9600);
  
  Serial.println("INIT");
}

void loop() {
  updateEncoder();
}

void updateEncoder() {
  boolean A = digitalRead(encoderPinA);
  boolean B = digitalRead(encoderPinB);

  if (goStop == 0) {
    goStop = 1;
  } else {

    if (ALast == A && BLast == B) {
      //Serial.println(".");
    } else {

      int nextStep = 0;
      
      if (ALast == 0 && BLast == 0) {
        if (A == 1 && B == 0) {
          nextStep++;
        } else if (A == 0 && B == 1) {
          nextStep--;
        }
      } else if (ALast == 1 && BLast == 0) {
        if (A == 1 && B == 1) {
          nextStep++;
        } else if (A == 0 && B == 0) {
          nextStep--;
        }
      } else if (ALast == 1 && BLast == 1) {
        if (A == 0 && B == 1) {
          nextStep++;
        } else if (A == 1 && B == 0) {
          nextStep--;
        }
      } else if (ALast == 0 && BLast == 1) {
        if (A == 0 && B == 0) {
          nextStep++;
        } else if (A == 1 && B == 1) {
          nextStep--;
        }
      }

      if (nextStep != 0) {
        if (lastMovement != nextStep) {
            lastMovement = nextStep;
        } else {
          Serial.println(nextStep);
          goStop = 0;
        }
      }
    }
  }

  ALast = A;
  BLast = B;
  
}

