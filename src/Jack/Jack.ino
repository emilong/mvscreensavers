#include <MicroView.h>

#define STRING "all work and no play make jack a dull boy"
#define DELAY_MIN 30
#define DELAY_MAX 400

class Jack {
  private:
  String _string;
  int _i;
  char _nextChar;

  void generateNextChar();

  public:
  Jack(const String string);
  char nextChar();
  bool hasMore();
  void reset();
};

void Jack::generateNextChar() {
   while (_i < _string.length()) {
    int modification = random(100);

    // most of the time, just return the next character
    if (modification < 70) {
      _nextChar = _string.charAt(_i++);
      return;
    }

    // 20% of the time, upper case the character
    if (modification < 90) {
      _nextChar = (char) toupper(_string.charAt(_i++));
      return;
    }

    // 5% of the time, delete a character
    if (modification < 95) {
      _i++;
      continue;
    }

    // 5% of the time, insert a double
    if (modification < 100) {
      _nextChar = _string.charAt(_i);
      return;
    }
  };

  _nextChar = '\0';
}

Jack::Jack(const String string) {
  _i = 0;
  _string = string;
  generateNextChar();
}

char Jack::nextChar() {
  char nextChar = _nextChar;
  generateNextChar();

  return nextChar;
}

bool Jack::hasMore() {
  return _nextChar != '\0';
}

void Jack::reset() {
  _i = 0;
  generateNextChar();
}

Jack jack(STRING);

void setup() {
  uView.begin();
  uView.clear(PAGE);
  uView.display();

  randomSeed(analogRead(0));
}


void loop () {
  uView.clear(PAGE);
  uView.setCursor(0, 0);
  while (jack.hasMore()) {
    delay(random(DELAY_MIN, DELAY_MAX));
    uView.write(jack.nextChar());
    uView.display();
  }
  jack.reset();
}
