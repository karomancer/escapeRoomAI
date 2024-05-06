void wakeup() {
  ring.setBrightness(30);
  for (uint32_t c = 0x00ff90; c; c >>= 6) {
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(50);
    }
  }
}

void listen() {
  ring.setBrightness(30);
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, 0xFFFFFF);
    ring.show();
  }
  for (int j = 20; j < 31; j++) {
    ring.setBrightness(j);
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, 0xFFFFFF);
      ring.show();
    }
  }
  delay(30);
}

void think() {
  ring.setBrightness(20);
  for (uint32_t c = 0xFFFFFF; c; c >>= 1) {
    for (int i = 0; i < ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(10);
    }
  }
}

void sleep() {
  ring.setBrightness(20);
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, 0x1FDEB4);
    ring.show();
    delay(10);
  }
  delay(200);
  clearLight();
}

void errorMic() {
  clearLight();
  for (int i = 0; i < ring.numPixels() / 2; i++) {
    ring.setPixelColor(i, 0xFF0000);
    ring.show();
    delay(10);
  }
}

void errorSpeaker() {
  clearLight();
  for (int i = 0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, 0xFF0000);
    ring.show();
    delay(10);
  }
}

void clearLight() {
  ring.setBrightness(30);
  ring.clear();
  ring.show();
}
