#include <Arduino.h>
#include <Servo.h>

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

// ultrasonic
const int TRIG_PIN = A1;
const int ECHO_PIN = A2;

// servos
const int SERVO_1_PIN = 13;
const int SERVO_2_PIN = 14;
Servo servo1;
Servo servo2;


////////////////////////////////////// CONSTANTS ////////////////////////////////////// 
const int LINE_THRES = 30; // idk
const int OBS_THRES = 15; // cm
const int NOTHING_THRES = 30; // cm

////////////////////////////////////// VARIABLES ////////////////////////////////////// 

// line follow
bool GO_LEFT = true;
bool GO_RIGHT = false;
bool lastDirection = GO_LEFT;
bool on_black = true;

// red
int num_obstacles = 0;
bool clearing_obstacle = false;
int stage = 0;


////////////////////////////////////// INIT ////////////////////////////////////// 

// loops
void motortest();
void irtest();
void colortest();
void ultrasonictest();
void servotest();

void red();

// simple
void forward();
void backward();
void stop();
void weak_left();
void weak_right();
void hard_left();
void hard_right();
void left_90();
void right_90();
void left_45();
void right_45();

bool check_line();
long get_distance();
bool check_obstacle();

// bigger
void linefollow();
void obstacle_left(); // reroute around on the left
void obstacle_right(); // right


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

  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
}


void loop() {
  // motortest();
  // irtest();
  // colortest();
  // ultrasonictest();
  // servotest();

  ////////////////////////////////////// red
  if (check_obstacle()) {
    if (num_obstacles == 0) {
      obstacle_left();
    } else {
      obstacle_right();
    }
  }
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
  Serial.println(intensity);
  delay(200);
}

void ultrasonictest() {
  long distance = get_distance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance != 0) {
    if (distance < NOTHING_THRES) {
      Serial.println("Something");
    }

    if (distance < OBS_THRES) {
      Serial.println("OBSTACLE");
    }

    if (distance < 10) {
      Serial.println("moooooooo");
    }
  }

  delay(200);
}

void servotest() {
  Serial.println("Servos to 0");
  servo1.write(0);
  servo2.write(0);
  delay(1000);

  Serial.println("Servos to 90");
  servo1.write(90);
  servo2.write(90);
  delay(1000);

  Serial.println("Servos to 180");
  servo1.write(180);
  servo2.write(180);
  delay(1000);
}

void red() {
  if (check_obstacle() or clearing_obstacle) {
    if (num_obstacles == 0) {
      obstacle_left();
    } else {
      obstacle_right();
    }
  } 
  
  else {
    linefollow();
  }


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

void hard_left() {
  digitalWrite(MOTORAFRONT, LOW);
  digitalWrite(MOTORABACK, HIGH);
  digitalWrite(MOTORBFRONT, HIGH);
  digitalWrite(MOTORBBACK, LOW);
}

void hard_right() {
  digitalWrite(MOTORAFRONT, HIGH);
  digitalWrite(MOTORABACK, LOW);
  digitalWrite(MOTORBFRONT, LOW);
  digitalWrite(MOTORBBACK, HIGH);
}

void left_90() {
  hard_left();
  delay(1);
}

void right_90() {
  hard_right();
  delay(1);
}

void left_45() {
  hard_left();
  delay(1);
}

void right_45() {
  hard_right();
  delay(1);
}

bool check_line() {
  int intensity = pulseIn(SENSOR_OUT, LOW);

  if (intensity > LINE_THRES) {
    return true;
  } else {
    return false;
  }
}

long get_distance() {
  digitalWrite(TRIG_PIN, LOW); // clean
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // time in microseconds (us)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  
  // Math: d = (t * v_sound) / 2 (there and back)
  // v_sound = 0.034 cm/us
  long cm = duration * 0.034 / 2;
  return cm;
}

bool check_obstacle() {
  long distance = get_distance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance < OBS_THRES && distance != 0) {
    clearing_obstacle = true;
    return true;
  } else {
    return false;
  }
}

////////////////////////////////////// BIGGER FUNCTIONS ////////////////////////////////////// 

void linefollow() {
  if (check_line()) {
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

void obstacle_left() {
  // STAGE 0
  if (stage == 0) {
    hard_left();
    delay(100);
    long distance = get_distance();

    if (distance > NOTHING_THRES || distance == 0) {
      stage = 1;
      forward();
      delay(500);
    }
  }

  // STAGE 1
  else if (stage == 1) {
    right_45();
    long distance = get_distance();

    if (distance > OBS_THRES || distance == 0) {
      stage = 2;
      forward();
      delay(500);
    } else {
      left_45();
      forward();
      delay(200);
    }
  }

  // STAGE 2
  else if (stage == 2) {
    if (check_line()) {
      stage = 0;
      num_obstacles++;
      clearing_obstacle = false;
      lastDirection = GO_LEFT;
      Serial.println("OBSTACLE 1 COMPLETE");
    } else {
      forward();
      delay(100);
    }
  }
}