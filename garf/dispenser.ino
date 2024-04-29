#include <Servo.h>

const int INC = 9;

int pos = 0;
int count = 0;

void openFirstGate() {
  for (pos = MAX; pos >= MIN; pos -= INC) {
    firstGate.write(pos);
    delay(15);
  }

  delay(200);

  for (pos = MIN; pos <= MAX; pos += INC) {
    firstGate.write(pos);
    delay(15);
  }
}

void openSecondGate() {
  for (pos = MIN; pos <= MAX; pos += INC) {
    secondGate.write(pos);
    delay(15);
  }

  delay(1000);

  for (pos = MAX; pos >= MIN; pos -= INC) {
    secondGate.write(pos);
    delay(15);
  }
}

void dispensePill() {
  openFirstGate();
  openSecondGate();
}
