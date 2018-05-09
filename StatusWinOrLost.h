/**
 * Status win or lost:
 * Wait a time checking the swith win and lost.
 * If sensor win ON then STATUS_WIN
 * If sensor lost ON then STATUS_LOST
 * If lostTime pass and no detect nothing then STATUS_LOST
 */
boolean isWinOrLostActivate;
unsigned long lostTime;

void statusWinOrLost_Reset() {
	isWinOrLostActivate = false;
}

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