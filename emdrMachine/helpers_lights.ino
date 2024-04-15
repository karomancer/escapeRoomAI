const int SPEED = 100;
const uint32_t CYAN = NeoPixel.Color(0, 255, 255);
const uint32_t BLUE = NeoPixel.Color(0, 0, 120);

enum Direction { FORWARDS,
                 BACKWARDS };

void animateBinaryForward(int* binary, int pixelOffset = 0) {
  for (int pixel = 0; pixel < NUM_PIXELS - NUM_BIN_PLACES; pixel++) {
    NeoPixel.clear();
    for (int digit = 0; digit < NUM_BIN_PLACES; digit++) {
      NeoPixel.setPixelColor(digit + pixel, binary[digit] ? CYAN : BLUE);
    }
    NeoPixel.show();
    delay(SPEED);
  }
}

void animateBinaryBackward(int* binary, int pixelOffset = 0) {
  for (int pixel = NUM_PIXELS - 1; pixel > NUM_BIN_PLACES - 1; pixel--) {
    NeoPixel.clear();
    for (int digit = 0; digit < NUM_BIN_PLACES; digit++) {
      NeoPixel.setPixelColor(pixel - digit - 1, binary[NUM_BIN_PLACES - digit - 1] ? CYAN : BLUE);
    }
    NeoPixel.show();
    delay(SPEED);
  }
}

// direction is 1 for forward from cable, -1 to return to cable
void animateLetter(char letter, Direction direction = FORWARDS) {
  int binary[NUM_BIN_PLACES];
  itob(letterMap[letter], binary);

  NeoPixel.clear();
  NeoPixel.setBrightness(10);

  direction == FORWARDS ? animateBinaryForward(binary) : animateBinaryBackward(binary);
  delay(800);
}

void clearSoftGlow(int brightness = 20) {
  NeoPixel.clear();
  NeoPixel.setBrightness(1);

  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(20, 20, 20));
  }
  NeoPixel.show();
}

void animateWord(char* word) {
  for (int x = 0; x < NUM_BIN_PLACES; x++) {
    int y = 10 * (int) sin(x / 2);
    clearSoftGlow(y);
    delay(1000 * y);
  }
  
  for (int i = 0; i < strlen(word); i++) {
    animateLetter(word[i], i % 2 == 0 ? FORWARDS : BACKWARDS);
  }
  
}