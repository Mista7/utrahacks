/*
 * L298N Dual Motor Driver Controller
 * Configurable via macros for easy pin and parameter changes
 */

// ========== MOTOR A CONFIGURATION ==========
#define MOTOR_A_EN    9   // PWM pin for Motor A speed control
#define MOTOR_A_IN1   8   // Motor A direction pin 1
#define MOTOR_A_IN2   7   // Motor A direction pin 2

// ========== MOTOR B CONFIGURATION ==========
#define MOTOR_B_EN    3   // PWM pin for Motor B speed control
#define MOTOR_B_IN1   5   // Motor B direction pin 1
#define MOTOR_B_IN2   4   // Motor B direction pin 2

// ========== MOTOR PARAMETERS ==========
#define MAX_SPEED     255     // Maximum PWM value (0-255)
#define DEFAULT_SPEED 200     // Default motor speed
#define MIN_SPEED     0       // Minimum speed (motor stopped)

// ========== MOTOR DIRECTIONS ==========
#define FORWARD   1
#define BACKWARD  2
#define BRAKE     3
#define COAST     4

// ========== HELPER MACROS ==========
#define CONSTRAIN_SPEED(speed) constrain(speed, MIN_SPEED, MAX_SPEED)

void setup() {
  // Initialize Motor A pins
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  
  // Initialize Motor B pins
  pinMode(MOTOR_B_EN, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);
  
  // Start with motors stopped
  stopMotors();
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("L298N Dual Motor Controller Ready");
}

void loop() {
  // Example usage - modify as needed
  
  // Move both motors forward at default speed
  setMotorA(FORWARD, DEFAULT_SPEED);
  setMotorB(FORWARD, DEFAULT_SPEED);
  delay(2000);
  
  // Stop both motors
  stopMotors();
  delay(1000);
  
  // Move both motors backward at half speed
  setMotorA(BACKWARD, DEFAULT_SPEED / 2);
  setMotorB(BACKWARD, DEFAULT_SPEED / 2);
  delay(2000);
  
  // Stop both motors
  stopMotors();
  delay(1000);
  
  // Turn right (Motor A forward, Motor B backward)
  setMotorA(FORWARD, DEFAULT_SPEED);
  setMotorB(BACKWARD, DEFAULT_SPEED);
  delay(1000);
  
  // Brake both motors
  brakeMotors();
  delay(2000);
}

// ========== MOTOR A CONTROL FUNCTIONS ==========
void setMotorA(int direction, int speed) {
  speed = CONSTRAIN_SPEED(speed);
  
  switch(direction) {
    case FORWARD:
      digitalWrite(MOTOR_A_IN1, HIGH);
      digitalWrite(MOTOR_A_IN2, LOW);
      analogWrite(MOTOR_A_EN, speed);
      break;
      
    case BACKWARD:
      digitalWrite(MOTOR_A_IN1, LOW);
      digitalWrite(MOTOR_A_IN2, HIGH);
      analogWrite(MOTOR_A_EN, speed);
      break;
      
    case BRAKE:
      digitalWrite(MOTOR_A_IN1, HIGH);
      digitalWrite(MOTOR_A_IN2, HIGH);
      analogWrite(MOTOR_A_EN, MAX_SPEED);
      break;
      
    case COAST:
      digitalWrite(MOTOR_A_IN1, LOW);
      digitalWrite(MOTOR_A_IN2, LOW);
      analogWrite(MOTOR_A_EN, 0);
      break;
  }
}

// ========== MOTOR B CONTROL FUNCTIONS ==========
void setMotorB(int direction, int speed) {
  speed = CONSTRAIN_SPEED(speed);
  
  switch(direction) {
    case FORWARD:
      digitalWrite(MOTOR_B_IN1, HIGH);
      digitalWrite(MOTOR_B_IN2, LOW);
      analogWrite(MOTOR_B_EN, speed);
      break;
      
    case BACKWARD:
      digitalWrite(MOTOR_B_IN1, LOW);
      digitalWrite(MOTOR_B_IN2, HIGH);
      analogWrite(MOTOR_B_EN, speed);
      break;
      
    case BRAKE:
      digitalWrite(MOTOR_B_IN1, HIGH);
      digitalWrite(MOTOR_B_IN2, HIGH);
      analogWrite(MOTOR_B_EN, MAX_SPEED);
      break;
      
    case COAST:
      digitalWrite(MOTOR_B_IN1, LOW);
      digitalWrite(MOTOR_B_IN2, LOW);
      analogWrite(MOTOR_B_EN, 0);
      break;
  }
}

// ========== CONVENIENCE FUNCTIONS ==========
void stopMotors() {
  setMotorA(COAST, 0);
  setMotorB(COAST, 0);
}

void brakeMotors() {
  setMotorA(BRAKE, 0);
  setMotorB(BRAKE, 0);
}

void setBothMotors(int direction, int speed) {
  setMotorA(direction, speed);
  setMotorB(direction, speed);
}