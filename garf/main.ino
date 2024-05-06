#include <Servo.h>

bool isWakingUp = true;
bool isChatting = false;
bool isThinking = false;
bool isListening = false;

void defaultAllMotors() {
  mouthServo.write(MIN_MOUTH_POS);
  tongueServo.write(MIN_TONGUE_POS);
  dispenserServo.write(MAX_GEAR_VALUE);
}

void attachAllMotors() {
  mouthServo.attach(MOUTH_PIN);
  tongueServo.attach(TONGUE_PIN);
  dispenserServo.attach(DISPENSER_PIN);
  defaultAllMotors();
}

void detachAllMotors() {
  defaultAllMotors();
  dispenserServo.detach();
  mouthServo.detach();
  tongueServo.detach();
}

void setup() {
  Serial.begin(9600);

  // Set up light
  ring.begin();
  ring.setBrightness(32);
  ring.show();

  attachAllMotors();
}

void loop() {
  while (!Serial.available()) {
    if (isWakingUp) {
      delay(100);
      detachAllMotors();
      wakeup();
    } else if (isThinking) {
      think();
    } else if (isListening) {
      listen();
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
    detachAllMotors();
    isChatting = false;
    isListening = true;
  } else {
    if (!mouthServo.attached() || !tongueServo.attached() || !dispenserServo.attached()) {
      attachAllMotors();
    }

    clearLight();
    isThinking = false;
    isListening = false;
    isChatting = false;
    if (command == "dispense") {
      dispensePill();
      stickTongueOut();
      delay(3000);
      pullTongueBackIn();
      delay(1000);
    } else if (command == "mouth open") {
      openMouth(MAX_MOUTH_POS);
    } else if (command == "chat") {
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
    }
  }
}
