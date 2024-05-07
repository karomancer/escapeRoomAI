#include <Servo.h>

bool isWakingUp = true;
bool isChatting = false;
bool isThinking = false;

void defaultAllMotors() {
  pullTongueBackIn();
  resetDispenserWheel();
  closeMouth();
}

void attachAllMotors() {
  mouthServo.attach(MOUTH_PIN);
  tongueServo.attach(TONGUE_PIN);
  dispenserServo.attach(DISPENSER_PIN);
}

void detachAllMotors() {
  dispenserServo.detach();
  mouthServo.detach();
  tongueServo.detach();
}

void setup() {
  Serial.begin(9600);

  attachAllMotors();
  defaultAllMotors();
  detachAllMotors();

  // Set up light
  ring.begin();
  ring.setBrightness(32);
  ring.show();
}

void loop() {
  while (!Serial.available()) {
    if (isWakingUp) {
      delay(100);
      wakeup();
    } else if (isThinking) {
      think();
    } else {
      if (isChatting) {
        chat();
      }
    }
  };
  String command = Serial.readString();
  isWakingUp = false;
  if (command == "think") {
    detachAllMotors();
    isThinking = true;
  } else if (command == "listen") {
    isChatting = false;
    detachAllMotors();
    listen();
  } else {
    if (!mouthServo.attached() || !tongueServo.attached() || !dispenserServo.attached()) {
      attachAllMotors();
    }

    clearLight();
    isThinking = false;
    isChatting = false;
    if (command == "dispense") {
      dispensePill();
      stickTongueOut();
      delay(12000);
      pullTongueBackIn();
      delay(1000);
    } else if (command == "mouth open") {
      openMouth(MAX_MOUTH_POS);
    } else if (command == "mouth close") {
      closeMouth();
    } else if (command == "chat start") {
      isChatting = true;
    } else if (command == "wake") {
      detachAllMotors();
      wakeup();
      attachAllMotors();
    } else if (command == "sleep") {
      detachAllMotors();
      sleep();
      attachAllMotors();
    } else if (command == "error mic") {
      detachAllMotors();
      errorMic();
    } else if (command == "error speaker") {
      detachAllMotors();
      errorSpeaker();
    } else if (command == "reset") {
      bool isWakingUp = true;
      bool isChatting = false;
      bool isThinking = false;
    }
  }
}
