/* #include "linefollower.h"
#include "rgb.h"
#include <Arduino.h>

bool isBlack(const RGB& color) {
  const int BLACK_THRESHOLD = 50; // Adjust threshold as needed
  return (color.r < BLACK_THRESHOLD && color.g < BLACK_THRESHOLD && color.b < BLACK_THRESHOLD);
}

void followLine() {
  RGB color = readRGB();

  if (isBlack(color)) {
    moveForward();        // stay on line
  } else {
    stopMotors();         // lost line (basic behavior)
  } */