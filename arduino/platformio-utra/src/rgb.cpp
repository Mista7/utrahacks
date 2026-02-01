////////////////////////////////////// COLOR DETECTION ////////////////////////////////////// 

#include "rgb.h"

// calibration
// Put the sensor over WHITE and record the pulseIn values
const int W_RED = 20, W_GREEN = 25, W_BLUE = 20;
// Put the sensor over BLACK and record the pulseIn values
const int B_RED = 200, B_GREEN = 220, B_BLUE = 200;

struct RGB {
  int r, g, b;
};

RGB readRGB() {
  RGB color;

  // Read red
  digitalWrite(S2, LOW); digitalWrite(S3, LOW);
  color.r = map(pulseIn(SENSOR_OUT, LOW), B_RED, W_RED, 0, 255);

  // Read blue
  digitalWrite(S2, LOW); digitalWrite(S3, HIGH);
  color.b = map(pulseIn(SENSOR_OUT, LOW), B_BLUE, W_BLUE, 0, 255);

  // Read green
  digitalWrite(S2, HIGH); digitalWrite(S3, HIGH);
  color.g = map(pulseIn(SENSOR_OUT, LOW), B_GREEN, W_GREEN, 0, 255);

  color.r = constrain(color.r, 0, 255);
  color.g = constrain(color.g, 0, 255);
  color.b = constrain(color.b, 0, 255);

  return color;
}

void identifyColor() {
  RGB data = readRGB();
  
  Serial.print("R: "); Serial.print(data.r);
  Serial.print(" G: "); Serial.print(data.g);
  Serial.print(" B: "); Serial.println(data.b);

  if (data.r > 200 && data.g < 100 && data.b < 100) {
    Serial.println("Detected: RED");
  } else if (data.g > 200 && data.r < 100) {
    Serial.println("Detected: GREEN");
  } else if (data.r < 50 && data.g < 50 && data.b < 50) {
    Serial.println("Detected: BLACK");
  } else {
    Serial.println("Detected: UNKNOWN");
  }
}