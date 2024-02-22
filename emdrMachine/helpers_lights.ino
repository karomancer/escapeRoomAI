void animateLetter(char letter) {
  int binary[NUM_BIN_PLACES];
  itob(letterMap[letter], binary);

  NeoPixel.clear();
  NeoPixel.setBrightness(10);
  int pixel = 0;
  for (int pixel = 0; pixel < NUM_PIXELS - NUM_BIN_PLACES; pixel++) {
    NeoPixel.clear();
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(50, 50, 50));
    for (int digit = 0; digit < NUM_BIN_PLACES; digit++) {
      NeoPixel.setPixelColor(digit + pixel, binary[digit] ? NeoPixel.Color(0, 255, 255) : NeoPixel.Color(0, 0, 45));
    }
    NeoPixel.show();
    delay(100);
  }
  delay(1000);
}

void clearSoftGlow() {
  NeoPixel.clear();
  NeoPixel.setBrightness(1);

  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 255, 255));
  }
  NeoPixel.show();
}

void lightsAnimation() {
  NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  NeoPixel.setBrightness(5);

  // turn pixels to green one-by-one with delay between each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
    NeoPixel.show();                                           // update to the NeoPixel Led Strip

    delay(500);  // 500ms pause between each pixel
  }

  // turn off all pixels for two seconds
  NeoPixel.clear();
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(2000);      // 2 seconds off time

  // turn on all pixels to red at the same time for two seconds
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
  }
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(1000);      // 1 second on time

  // turn off all pixels for one seconds
  NeoPixel.clear();
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(1000);      // 1 second off time
}