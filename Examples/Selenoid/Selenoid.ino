const int BAUDS = 9600;
const int SOLENOID_PIN = 47;
const int WAIT_TIME = 3000;

void setup() {
	Serial.begin(BAUDS);
	pinMode(SOLENOID_PIN, OUTPUT);    
}


void loop() {
  
	Serial.println("Run!");

	digitalWrite(SOLENOID_PIN, HIGH);
	delay(WAIT_TIME);

	digitalWrite(SOLENOID_PIN, LOW);
	delay(WAIT_TIME);
}
