/**
 * Variables and Arduino pins 
 * 
*/
const int BAUDS = 9600;

const int STATUS_STAND_BY = -1;
const int STATUS_INIT = 0;
const int STATUS_ACTIVATE_GAME = 1;

const int DETECT_COIN_PIN = 6;
const int ENABLE_COIN_MACHINE_PIN = 7;

const int MUSIC_RX_PIN = 10;
const int MUSIC_TX_PIN = 11;

const int DELAY_AFTER_STATUS_INIT = 2000;
const int DELAY_AFTER_INSERT_COIN = 3000;

const int MUSIC_VOLUME = 25; //Set volume value. From 0 to 30