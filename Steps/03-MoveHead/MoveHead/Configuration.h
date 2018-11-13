/**
 * Variables and Arduino pins 
 * 
*/
const int BAUDS = 9600;

const int STATUS_STAND_BY = -1;
const int STATUS_INIT = 0;
const int STATUS_ACTIVATE_GAME = 1;
const int EYES_LED_PIN = 3;

const int DETECT_COIN_PIN = 6;
const int ENABLE_COIN_MACHINE_PIN = 7;

const int HEAD_SERVO_PIN = 9;

const int MUSIC_RX_PIN = 10;
const int MUSIC_TX_PIN = 11;

const int INIT_HEAD_SERVO_POSITION = 83;
const int MAX_HEAD_SERVO_POSITION = 40;
const int STEP_HEAD_SERVO_POSITION = 2;

const int DELAY_AFTER_STATUS_INIT = 2000;
const int DELAY_AFTER_INSERT_COIN = 3000;

const int MUSIC_VOLUME = 30; //Set volume value. From 0 to 30