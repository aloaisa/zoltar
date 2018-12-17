int MONEY_MACHINE = 9;
int RELE = 8;

void setup() {
  Serial.begin(9600);
  pinMode(RELE, OUTPUT);
  pinMode(MONEY_MACHINE, INPUT);
  digitalWrite(RELE, HIGH);
}

void loop() {
  
  int money = digitalRead(MONEY_MACHINE);
  //Serial.println(money);
  if (money == HIGH) {
    
    digitalWrite(RELE, LOW);

    Serial.println("MONEDA");
    Serial.println("Desactivado");
    
    delay(10000);

    digitalWrite(RELE, HIGH);
    Serial.println("Activado");
  }

}
