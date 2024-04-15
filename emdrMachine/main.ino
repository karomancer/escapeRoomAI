#include <Adafruit_NeoPixel.h>

void setup(void) {
  Serial.begin(9600);
  NeoPixel.begin();
  setupLetters();
  while (!Serial)
    ;
}

void loop(void) {
  animateWord("league");
}