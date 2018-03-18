const int BAUDS = 9600;

const int STATUS_STAND_BY = -1;
const int STATUS_INIT = 0;
const int STATUS_ACTIVATE_GAME = 1;
const int STATUS_WAITING_RELEASE_COIN = 2;
const int STATUS_WIN_OR_LOST = 3;
const int STATUS_WIN = 4;
const int STATUS_LOST = 5;
const int STATUS_OFF = 6;

const int BACKGROUND_LED_PIN = 2;
const int EYES_LED_PIN = 3;
const int POINT_TO_MOUTH_LED_PIN = 4;
const int PUSH_BUTTON_COIN_LED_PIN = 5;
const int DETECT_COIN_PIN = 7;
const int MUSIC_RX_PIN = 10;
const int MUSIC_TX_PIN = 11;
const int MUSIC_VOLUME = 25; //Set volume value. From 0 to 30
const int SOUND_RX_PIN = 12;
const int SOUND_TX_PIN = 13;
const int SOUND_VOLUME = 6; //Set volume value. From 0 to 30

const int POINT_TO_MOUTH_WAIT_TIME = 20000;

const int DELAY_AFTER_STATUS_INIT = 5000; // en milisegundos

const int SERVO_CONTROL_X_PIN = 53;
const int SERVO_CONTROL_X_STOP = 1500;
const int SERVO_CONTROL_X_RIGHT = 1600;
const int SERVO_CONTROL_X_LEFT = 1250;

const int CONTROLS_DT_PIN = 22;
const int CONTROLS_CLK_PIN = 23;

