#include <Servo.h>
#include <Adafruit_NeoPixel.h>

/**
 * Pin declarations
 **/
#define LED_PIN        2
#define DISPENSER_PIN  3
#define TONGUE_PIN     5
#define MOUTH_PIN      6

/**
 * Loading light
 **/ 
#define NUM_PIXELS    16

Adafruit_NeoPixel ring(NUM_PIXELS, LED_PIN, NEO_GRB);

/**
 * Dispenser constants
 **/
#define MIN_GEAR_VALUE 0
#define MAX_GEAR_VALUE 180

Servo dispenserServo;

/**
 * Mouth constants
 **/
#define MIN_MOUTH_POS   25
#define MAX_MOUTH_POS   105 // 95 to chat, max 130 to install

#define MIN_TONGUE_POS  46
#define MAX_TONGUE_POS  105

Servo mouthServo;
Servo tongueServo;
