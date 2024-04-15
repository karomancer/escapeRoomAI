String letters = "abcdefghijklmnopqrstuvwxyz0123456789";
std::map<char, int> letterMap;

void setupLetters() {
  for (int i = 0; i < letters.length(); i++) {
    letterMap[letters[i]] = i;
  }
}

void itob(int num, int *binary) {
  for (int i = 0; i < NUM_BIN_PLACES; i++) {
    int digit = 0;
    int currPow = (int)pow(2, NUM_BIN_PLACES - i - 1);
    if (num >= currPow) {
      digit = 1;
      num -= currPow;
    }
    binary[i] = digit;
  }
}

