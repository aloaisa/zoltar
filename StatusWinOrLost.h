// Chequeamos los sensores de acierto o no
// Si ha acertado pasamos a "WIN" sino a "LOST"

// Sensores acierto o no - 2 digital inputs
boolean isWinOrLostActivate = false;
unsigned long lostTime;

boolean isWin() {
	int input = digitalRead(SENSOR_WIN_PIN);
	if (input == HIGH) {
		return true;
	}

	return false;
}

boolean isLost() {
	if (lostTime < millis()) {
    	return true;
  	}

  	int input = digitalRead(SENSOR_LOST_PIN);
	if (input == HIGH) {
		return true;
	}

	return false;
}

int statusWinOrLost(int status) {
	if (isWinOrLostActivate == false) {
		lostTime = millis() + WAIT_LOST_TIME;
		isWinOrLostActivate = true;
	}

	if (isWin() == true) {
		return STATUS_WIN;
	} else if (isLost() == true) {
		return STATUS_LOST;
	}

	return status;
}