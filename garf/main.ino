#include <Servo.h>

bool isChatting = false;

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
  pinMode(BTN, INPUT);

  firstGate.attach(FIRST_GATE);
  firstGate.write(MAX);

  secondGate.attach(SECOND_GATE);
  secondGate.write(MIN);
}

void loop() {
  while (!Serial.available()) {
    if (isChatting) {
      chat();
    }
  };
  String command = Serial.readString();
  if (command == "chat") {
    isChatting = !isChatting;
    delay(isChatting ? 0 : 250);
  } 
  
  if (command == "dispense") {
    dispensePill();
    stickTongueOut();
    delay(3000);
    pullTongueBackIn();
    delay(1000);
  }

  // Test pill dispensing with button
  // if (digitalRead(BTN) == HIGH) {
  //   dispensePill();
  //   stickTongueOut();
  //   delay(3000);
  //   pullTongueBackIn();
  //   delay(1000);
  // }
}
