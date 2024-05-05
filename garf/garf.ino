#include <Servo.h>

/**
 * Dispenser constants
 **/
const int DISPENSER_PIN = 3;

Servo dispenserServo;

const int MIN_GEAR_VALUE = 0;
const int MAX_GEAR_VALUE = 175;

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
