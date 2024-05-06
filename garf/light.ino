void wakeup() {
  for (uint32_t c = 0xFF000000; c; c >>= 6) {
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(50);
    }
  }
}

void think() {
  for (uint32_t c = 0xFFFFFF; c; c >>= 1) {
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(10);
    }
  }
}

void sleep() {
  for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, 0x1FDEB4);
      ring.show();
      delay(10);
    }
  delay(200);
  clearLight();
}

void clearLight() {
  ring.clear();
  ring.show();
}
