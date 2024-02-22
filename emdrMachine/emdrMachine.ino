#include <math.h>
#include <vector>
#include <map>

#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL 12  // The ESP32 pin GPIO16 connected to NeoPixel
#define NUM_PIXELS 60     // The number of LEDs (pixels) on NeoPixel LED strip

#define NUM_BIN_PLACES 6

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRBW + NEO_KHZ800);
