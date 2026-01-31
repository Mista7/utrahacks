#include <Arduino.h>

const int MOTORAFRONT = 1;
const int MOTORABACK = 2;

const int MOTORBFRONT = 3;
const int MOTORBBACK = 4;

void forward();
void backward();
void stop();

void setup() {
  pinMode(MOTORAFRONT, OUTPUT);
  pinMode(MOTORABACK, OUTPUT);
  pinMode(MOTORBFRONT, OUTPUT);
  pinMode(MOTORBBACK, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
  Serial.println("F");
  forward();
  delay(2000);

  Serial.println("S");
  stop();
  delay(1000);

  Serial.println("B");
  backward();
  delay(2000);

  Serial.println("S");
  stop();
  delay(1000);
}

void forward() {
  digitalWrite(MOTORAFRONT, HIGH);
  digitalWrite(MOTORABACK, LOW);
  digitalWrite(MOTORBFRONT, HIGH);
  digitalWrite(MOTORBBACK, LOW);
}

void backward() {
  digitalWrite(MOTORAFRONT, LOW);
  digitalWrite(MOTORABACK, HIGH);
  digitalWrite(MOTORBFRONT, LOW);
  digitalWrite(MOTORBBACK, HIGH);
}

void stop() {
  digitalWrite(MOTORAFRONT, LOW);
  digitalWrite(MOTORABACK, LOW);
  digitalWrite(MOTORBFRONT, LOW);
  digitalWrite(MOTORBBACK, LOW);
}