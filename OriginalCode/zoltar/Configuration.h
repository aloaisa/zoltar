/**
 * Variables and Arduino pins 
 * 
*/
const int BAUDS = 9600;

const int STATUS_STAND_BY = -1;
const int STATUS_INIT = 0;
const int STATUS_ACTIVATE_GAME = 1;
const int STATUS_WAITING_RELEASE_COIN = 2;
const int STATUS_WIN_OR_LOST = 3;
const int STATUS_WIN = 4;
const int STATUS_LOST = 5;
const int STATUS_OFF = 6;

const int MAKE_WISH_LED_PIN = 2;        // Done
const int EYES_LED_PIN = 3;             // Done
const int POINT_TO_MOUTH_LED_PIN = 4;   // Done
const int PUSH_BUTTON_COIN_LED_PIN = 5; // done
const int DETECT_COIN_PIN = 6;          // Done
const int ENABLE_COIN_MACHINE_PIN = 7;  // Done

const int HEAD_SERVO_PIN = 9; // Done

const int MUSIC_RX_PIN = 10; // Done
const int MUSIC_TX_PIN = 11; // Done
const int SOUND_RX_PIN = 12; // Done
const int SOUND_TX_PIN = 13; // Done

const int CONTROLS_VERTICAL_DT_PIN = 22;  // Done
const int CONTROLS_VERTICAL_CLK_PIN = 23; // Done
const int SERVO_VERTICAL_PIN = 24;        // Done

const int CONTROLS_HORIZONTAL_DT_PIN = 25;  // Done
const int CONTROLS_HORIZONTAL_CLK_PIN = 26; // Done
const int SERVO_HORIZONTAL_PIN = 27;        // Done

const int SOLENOID_PIN = 31;         // Done
const int FREE_COIN_BUTTON_PIN = 33; // Done
const int SENSOR_WIN_PIN = 35;       // Done

const int MOTOR_ENABLE_PIN = 39;          // Done
const int MOTOR_WIN_STEP_PIN = 41;        // Done
const int MOTOR_WIN_DIR_PIN = 43;         // Done
const int SWITCH_WIN_CARD_MOTOR_PIN = 45; // Done

const int MOTOR_LOST_STEP_PIN = 40;        // Done
const int MOTOR_LOST_DIR_PIN = 42;         // Done
const int SWITCH_LOST_CARD_MOTOR_PIN = 44; // Done

const int MOTOR_STEP_VELOCITY_DELAY = 50;

const int MUSIC_VOLUME = 25; //Set volume value. From 0 to 30
const int SOUND_VOLUME = 25; //Set volume value. From 0 to 30

const int POINT_TO_MOUTH_WAIT_TIME = 25000;
const int MAKE_WITH_WAIT_TIME = 5000;

const int DELAY_AFTER_STATUS_INIT = 2000;
const int DELAY_AFTER_INSERT_COIN = 3000;

const int FREE_COIN_TIME = 10000;
const int SELENOID_WAIT_TIME = 1000;

const int WAIT_LOST_TIME = 5000;

const int GAME_TOTAL_TIME_FINISH = 5000;
#define STEPS 512
