void think() {
  for (uint32_t c = 0xFFFFFF; c; c >>= 1) {
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(10);
    }
  }
}

void rainbowLight() {
  uint32_t elapsed, t, startTime = micros();
  for (;;) {
    t = micros();
    elapsed = t - startTime;
    if (elapsed > 5000000) break;  // Run for 5 seconds
    uint32_t firstPixelHue = elapsed / 32;
    for (int i = 0; i < ring.numPixels(); i++) {
      uint32_t pixelHue = firstPixelHue + (i * 65536L / ring.numPixels());
      ring.setPixelColor(i, ring.gamma32(ring.ColorHSV(pixelHue)));
    }
    ring.show();
  }
}

void clearLight() {
  ring.clear();
  ring.show();
}
