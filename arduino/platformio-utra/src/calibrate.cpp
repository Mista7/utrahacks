#include "calibrate.h"

int acc = 100;

void calibrate() {
    Serial.println(acc);
    hard_left();
    delay(acc);
    hard_right();
    delay(acc);

    acc += 10;
    delay(2000);
}