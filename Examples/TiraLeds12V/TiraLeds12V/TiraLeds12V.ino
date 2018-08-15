int RELE = 8;

void setup() {
  Serial.begin(9600);
  pinMode(RELE, OUTPUT);
}

void loop() {
  
  Serial.println("Enciendo...");
  digitalWrite(RELE, HIGH);
  delay(1);

  Serial.println("Apago...");
  digitalWrite(RELE, LOW);
  delay(1);
  
}
