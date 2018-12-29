int lastPushedButton;
unsigned long time_easter_egg;

void nano_Off() {
  digitalWrite(NANO_PIN, LOW);
}

void statusInit_StandBy() {
  nano_Off();
  digitalWrite(ENABLE_COIN_MACHINE_PIN, HIGH);
}

void nano_On() {
  digitalWrite(NANO_PIN, HIGH);
}

// void launchEasterEgg() {
//   nano_On();
//   delay(10000);
//   nano_Off();
// }

// void checkEasterEgg() {
//   int button = digitalRead(FREE_COIN_BUTTON_PIN);
//   if (button == HIGH) {
//     if (lastPushedButton == HIGH) {
//       if (time_easter_egg <= millis()) {
//         launchEasterEgg();
//       }
//     } else {
//       time_easter_egg = millis() + EASTER_EGG_TIME;
//       lastPushedButton = HIGH;
//     }

//   } else {
//     lastPushedButton = LOW;
//   } 

// }

int statusStandBy(int status) {
  int inputCoin = digitalRead(DETECT_COIN_PIN);

  if (inputCoin == HIGH) {
    status = STATUS_INIT;
    delay(TIME_BETWEEN_INSERT_COIN_AND_START_INIT_GAME);
    digitalWrite(ENABLE_COIN_MACHINE_PIN, LOW);
  }

  // checkEasterEgg();

  return status;
}
