#include <Servo.h>

/**
 * Dispenser constants
 **/
const int BTN = 2;
const int FIRST_GATE = 3;
const int SECOND_GATE = 4;

Servo firstGate;
Servo secondGate;

const int MIN = 35;
const int MAX = 175;

/**
 * Mouth constants
 **/
// const int MOUTH_PIN = 3;
const int MOUTH_PIN = 6;
const int MIN_MOUTH_POS = 25;
const int MAX_MOUTH_POS = 105; // 95 to chat, max 130 to install

const int TONGUE_PIN = 5;
const int MIN_TONGUE_POS = 38;
const int MAX_TONGUE_POS = 105;

Servo mouthServo;
Servo tongueServo;
