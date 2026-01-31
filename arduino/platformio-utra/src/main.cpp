#include <Arduino.h>

// motor
const int MOTORAFRONT = 2; // left
const int MOTORABACK = 3;
const int MOTORBFRONT = 4; // right
const int MOTORBBACK = 5;

// sensor IR (flying fish)
const int SENSOR_L = 6;
const int SENSOR_R = 7;

// sensor color (TCS230 Pins)
const int S0 = 8;
const int S1 = 9;
const int S2 = 10;
const int S3 = 11;
const int SENSOR_OUT = 12;

////////////////////////////////////// CONSTANTS ////////////////////////////////////// 
const int LINE_THRES = 40;

// basic
void forward();
void backward();
void stop();
void weak_left();
void weak_right();

void linefollow();

void motortest();
void irtest();
void colortest();

bool GO_LEFT = true;
bool GO_RIGHT = false;
bool lastDirection = GO_LEFT;
bool on_black = true;

void setup() {
  pinMode(MOTORAFRONT, OUTPUT);
  pinMode(MOTORABACK, OUTPUT);
  pinMode(MOTORBFRONT, OUTPUT);
  pinMode(MOTORBBACK, OUTPUT);

  pinMode(SENSOR_L, INPUT);
  pinMode(SENSOR_R, INPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);
    
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  // motortest();
  // irtest();
   colortest();
}

////////////////////////////////////// LOOPS ////////////////////////////////////// 

void motortest() {
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

void irtest() {
  int val = digitalRead(SENSOR_L);
  Serial.println(val);
  delay(200);
}

void colortest() {
  int intensity = pulseIn(SENSOR_OUT, LOW);
  Serial.print(intensity);
  delay(200);
}

////////////////////////////////////// SIMPLE FUNCTIONS ////////////////////////////////////// 

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

void weak_left() {
  digitalWrite(MOTORAFRONT, LOW);
  digitalWrite(MOTORABACK, LOW);
  digitalWrite(MOTORBFRONT, HIGH);
  digitalWrite(MOTORBBACK, LOW);
}

void weak_right() {
  digitalWrite(MOTORAFRONT, HIGH);
  digitalWrite(MOTORABACK, LOW);
  digitalWrite(MOTORBFRONT, LOW);
  digitalWrite(MOTORBBACK, LOW);
}

////////////////////////////////////// BIGGER FUNCTIONS ////////////////////////////////////// 

void linefollow() {
  int intensity = pulseIn(SENSOR_OUT, LOW);

  if (intensity > LINE_THRES) {
    forward();
    on_black = true;
  }

  else {
    if (on_black) {
      lastDirection = !lastDirection;
      on_black = false;
    }
    if (lastDirection == GO_LEFT) {
      weak_left();
    }
    else if (lastDirection == GO_RIGHT) {
      weak_right();
    }
  }

  Serial.println(lastDirection);
    
  delay(100);
}