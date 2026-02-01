#ifndef RGB_H
#define RGB_H

#include <Arduino.h>

extern const int S2;
extern const int S3;
extern const int SENSOR_OUT;

struct RGB {
  int r, g, b;
};

RGB readRGB();
void identifyColor();

#endif