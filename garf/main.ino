#include <Servo.h>

bool isChatting = false;
bool isDispensing = false;
bool isMouthOpening = false;

void setup() {
  Serial.begin(9600);

  /**
   * Set up dispenser
   **/
  mouthServo.attach(MOUTH_PIN);
  tongueServo.attach(TONGUE_PIN);

  mouthServo.write(MIN_MOUTH_POS);
  tongueServo.write(MIN_TONGUE_POS);

  /**
   * Set up mouth
   **/
  dispenserServo.attach(DISPENSER_PIN);
  dispenserServo.write(MAX_GEAR_VALUE);
}

void loop() {
  while (!Serial.available()) {
    if (isDispensing) {
      dispensePill();
      stickTongueOut();
      delay(3000);
      pullTongueBackIn();
      delay(1000);
      isDispensing = false;
    } else if (isChatting) {
      chat();
    } else if (isMouthOpening) {
      openMouth(MAX_MOUTH_POS);
      isMouthOpening = false;
    }
  };
  String command = Serial.readString();
  if (command == "dispense") {
    isDispensing = true;
  } else if (command == "chat start") {
    isChatting = true;
    delay(250);
  } else if (command = "mouth open") {
    isMouthOpening = true;
  } else {
    isChatting = false;
  }
}
