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
const int EYES_LED_PIN = 3;
const int POINT_TO_MOUTH_LED_PIN = 4;
const int PUSH_BUTTON_COIN_LED_PIN = 5;
const int DETECT_COIN_PIN = 6;
const int ENABLE_COIN_MACHINE_PIN = 7;

const int HEAD_SERVO_PIN = 9;

/////////////////////
// MUSIC AND SOUND //
/////////////////////
const int MUSIC_RX_PIN = 10;
const int MUSIC_TX_PIN = 11;
const int SOUND_RX_PIN = 12;
const int SOUND_TX_PIN = 13;

const int MUSIC_VOLUME = 25; //Set volume value. From 0 to 30
const int SOUND_VOLUME = 25; //Set volume value. From 0 to 30

///////////
// TIMES //
///////////
const int DELAY_AFTER_STATUS_INIT = 2000;
const int DELAY_AFTER_INSERT_COIN = 3000;

const int POINT_TO_MOUTH_WAIT_TIME = 25000;
const int MAKE_WITH_WAIT_TIME = 5000;
