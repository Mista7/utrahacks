////////////////////////////////////// COLOR DETECTION ////////////////////////////////////// 

#include "rgb.h"

// calibration
// Put the sensor over WHITE and record the pulseIn values
const int W_RED = 16, W_GREEN = 18, W_BLUE = 15;
// Put the sensor over BLACK and record the pulseIn values
const int B_RED = 127, B_GREEN = 150, B_BLUE = 126;

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

  if (data.r < 50 && data.g < 50 && data.b < 0) {
    Serial.println("Detected: BLACK");
  } else if (data.r > 230 && data.g > 230 && data.b > 230) {
    Serial.println("Detected: WHITE");
  } else if (data.r > 220 && data.g < 130 && data.b < 200) {
    Serial.println("Detected: RED");
  } else if (data.r < 180 && data.b > 230) {
    Serial.println("Detected: BLUE");
  } else if (data.g > 230 && data.r < 180) {
    Serial.println("Detected: GREEN");
  } else {
    Serial.println("Detected: UNKNOWN");
  }
}

bool isBlack(const RGB& color) {
  const int BLACK_THRESHOLD = 50; // Adjust threshold as needed
  return (color.r < BLACK_THRESHOLD && color.g < BLACK_THRESHOLD && color.b < BLACK_THRESHOLD);
}

bool isRed(const RGB& color){
  const int RED_THRESHOLD = 210;
  return (color.r > RED_THRESHOLD && color.g < RED_THRESHOLD && color.b < RED_THRESHOLD);

}