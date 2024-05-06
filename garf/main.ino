#include <Servo.h>

bool isChatting = false;
bool isThinking = false;

void defaultAllMotors() {
  mouthServo.write(MIN_MOUTH_POS);
  tongueServo.write(MIN_TONGUE_POS);
  dispenserServo.write(MAX_GEAR_VALUE);
}

void attachAllMotors() {
  defaultAllMotors();
  mouthServo.attach(MOUTH_PIN);
  tongueServo.attach(TONGUE_PIN);
  dispenserServo.attach(DISPENSER_PIN);
}

void detachAllMotors() {
  defaultAllMotors();
  dispenserServo.detach();
  mouthServo.detach();
  tongueServo.detach();
}

void setup() {
  Serial.begin(9600);
  attachAllMotors();
  /**
   * Set up light
   **/
  ring.begin();
  ring.setBrightness(32);
  ring.show();
}

void loop() {
  while (!Serial.available()) {
    if (isThinking) {
      detachAllMotors();
      think();
    } else {
      if (!mouthServo.attached()) {
        attachAllMotors();
      }
      
      if (isChatting) {
        chat();
      }
    }
  };
  String command = Serial.readString();
  if (command == "think") {
    isThinking = true;
  } else {
    isThinking = false;
    if (command == "dispense") {
      dispensePill();
      stickTongueOut();
      delay(3000);
      pullTongueBackIn();
      delay(1000);
    } else if (command == "mouth open") {
      openMouth(MAX_MOUTH_POS);
    } else if (command == "chat start") {
      isChatting = true;
      delay(250);
    } else {
      isChatting = false;
    }
  }
}
