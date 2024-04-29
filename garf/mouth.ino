#include <Servo.h>

const int OFFEST_TIME = 60;

int mouthPos = 0;
int tonguePos = 0;

void stickTongueOut() {
  // Open mouth, stick out tongue
  for (mouthPos = MIN_MOUTH_POS; mouthPos <= MAX_TONGUE_POS; mouthPos++) {
    mouthServo.write(mouthPos);

    if (mouthPos > MAX_MOUTH_POS - OFFEST_TIME) {
      tongueServo.write(tonguePos += 2);
    }

    delay(20);
  }

  while (tonguePos <= MAX_TONGUE_POS) {
    tongueServo.write(tonguePos++);
    delay(20);
  }
}

void pullTongueBackIn() {
  for (tonguePos = MAX_TONGUE_POS; tonguePos >= MIN_TONGUE_POS; tonguePos--) {
    tongueServo.write(tonguePos);


    if (tonguePos < MAX_TONGUE_POS - OFFEST_TIME) {
      mouthServo.write(--mouthPos);
    }
    delay(20);
  }

  // Close mouth, put tongue back in
  while (mouthPos >= MIN_MOUTH_POS) {
    mouthServo.write(mouthPos--);
    delay(20);
  }

  mouthServo.write(MIN_MOUTH_POS);
  tongueServo.write(MIN_TONGUE_POS);
}

void openMouth() {
  for (mouthPos = MIN_MOUTH_POS; mouthPos <= MAX_TONGUE_POS / 4; mouthPos++) {
    mouthServo.write(mouthPos);
    delay(random(1, 20));
  }
}

void closeMouth() {
  // Close mouth, put tongue back in
  while (mouthPos >= MIN_MOUTH_POS) {
    mouthServo.write(mouthPos--);
    delay(random(1, 20));
  }

  mouthServo.write(MIN_MOUTH_POS);
}

void chat() {
  openMouth();
  closeMouth();
  delay(random(1, 10));
}