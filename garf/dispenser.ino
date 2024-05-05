#include <Servo.h>

const int INC = 2;

int pos = 0;
int count = 0;

void turnDispenserWheel() {
  for (pos = MAX_GEAR_VALUE; pos >= MIN_GEAR_VALUE; pos -= INC) {
    dispenserServo.write(pos);
    delay(15);
  }

  delay(200);

  for (pos = MIN_GEAR_VALUE; pos <= MAX_GEAR_VALUE; pos += INC) {
    dispenserServo.write(pos);
    delay(15);
  }
}

void dispensePill() {
  turnDispenserWheel();
}
