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
const int DETECT_COIN_PIN = 6;

const int MUSIC_RX_PIN = 10;
const int MUSIC_TX_PIN = 11;
const int SOUND_RX_PIN = 12;
const int SOUND_TX_PIN = 13;

const int SOLENOID_PIN = 31;
const int FREE_COIN_BUTTON_PIN = 33;
const int SENSOR_WIN_PIN = 35;
const int SENSOR_LOST_PIN = 37;

const int MOTOR_STEP_VELOCITY_DELAY = 50;

const int MOTOR_WIN_ENABLE_PIN = 39;
const int MOTOR_WIN_STEP_PIN = 41;
const int MOTOR_WIN_DIR_PIN = 43;
const int SWITCH_WIN_CARD_MOTOR_PIN = 45;

const int MOTOR_LOST_ENABLE_PIN = 38;
const int MOTOR_LOST_STEP_PIN = 40;
const int MOTOR_LOST_DIR_PIN = 42;
const int SWITCH_LOST_CARD_MOTOR_PIN = 44;


const int MUSIC_VOLUME = 25; //Set volume value. From 0 to 30
const int SOUND_VOLUME = 25; //Set volume value. From 0 to 30

const int POINT_TO_MOUTH_WAIT_TIME = 3000; //20000;

const int DELAY_AFTER_STATUS_INIT = 5000; // en milisegundos

//const int CONTROLS_DT_PIN = 22;
//const int CONTROLS_CLK_PIN = 23;

const int FREE_COIN_TIME = 10000;
const int SELENOID_WAIT_TIME = 1000;

const int WAIT_LOST_TIME = 5000;
#define STEPS 512


