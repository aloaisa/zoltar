/**
 * Variables and Arduino pins 
 * 
*/
const int BAUDS = 9600;

//////////////
// Statuses //
//////////////
const int STATUS_STAND_BY = -1;
const int STATUS_INIT = 0;
const int STATUS_ACTIVATE_GAME = 1;
const int STATUS_WAITING_RELEASE_COIN = 2;

//////////////
// PINS     //
//////////////
const int MAKE_WISH_LED_PIN = 2;
const int POINT_TO_MOUTH_LED_PIN = 4;
const int PUSH_BUTTON_COIN_LED_PIN = 5;
const int DETECT_COIN_PIN = 6;
const int ENABLE_COIN_MACHINE_PIN = 7;

const int NANO_PIN = 9;

const int CONTROLS_VERTICAL_DT_PIN = 22;
const int CONTROLS_VERTICAL_CLK_PIN = 23;
const int SERVO_VERTICAL_PIN = 24;

const int CONTROLS_HORIZONTAL_DT_PIN = 25;
const int CONTROLS_HORIZONTAL_CLK_PIN = 26;
const int SERVO_HORIZONTAL_PIN = 27;

const int SOLENOID_PIN = 31;

/////////////////////
// MUSIC AND SOUND //
/////////////////////
const int MUSIC_RX_PIN = 10;
const int MUSIC_TX_PIN = 11;
const int SOUND_RX_PIN = 12;
const int SOUND_TX_PIN = 13;

const int MUSIC_VOLUME = 30; //Set volume value. From 0 to 30
const int SOUND_VOLUME = 30; //Set volume value. From 0 to 30

///////////
// TIMES //
///////////
const int DELAY_AFTER_STATUS_INIT = 2000;
const int DELAY_AFTER_INSERT_COIN = 3000;

const int POINT_TO_MOUTH_WAIT_TIME = 25000;
const int MAKE_WITH_WAIT_TIME = 5000;

///////////////////////////
// CONTROLS SERVO LIMITS //
///////////////////////////
const int INIT_SERVO_VERTICAL_POSITION = 10;
const int MAX_SERVO_VERTICAL_POSITION = 140;
const int INIT_SERVO_HORIZONTAL_POSITION = 0;
const int MAX_SERVO_HORIZONTAL_POSITION = 85;
