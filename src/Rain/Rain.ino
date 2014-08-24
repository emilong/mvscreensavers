#include <MicroView.h>

#define DELAY_MIN 500
#define DELAY_MAX 3000
#define WIPE_CHANCE 30
#define WIPE_DELAY 50
#define RADIUS_MAX (min(LCDWIDTH, LCDHEIGHT) / 2)

void setup() {                
  uView.begin();
  uView.clear(PAGE);
  randomSeed(analogRead(0));
}

void wipe() {
  for (int x = 0; x < LCDWIDTH; x++) {
    uView.lineV(x, 0, LCDHEIGHT, BLACK, NORM);
    uView.display();
    delay(WIPE_DELAY);
  }
}

int shouldWipe() {
  return random(0, WIPE_CHANCE) == 0;
}

void loop() {
  int centerX = random(0, LCDWIDTH);
  int centerY = random(0, LCDHEIGHT);
  int radius = random(0, RADIUS_MAX);
  int delayTime = random(DELAY_MIN, DELAY_MAX);
  
  delay(delayTime);
  uView.circleFill(centerX, centerY, radius, WHITE, NORM);
  uView.circle(centerX, centerY, radius, BLACK, NORM);
  uView.display();

  if (shouldWipe()) {
    wipe();
  }
}
