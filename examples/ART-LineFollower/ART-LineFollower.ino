#include <ARTLibrary.h>

// Pin Definitions
#define IR_PIN_1 2
#define IR_PIN_2 3
#define IR_PIN_3 4
#define MOTOR_A_PIN_1 5
#define MOTOR_A_PIN_2 6
#define MOTOR_B_PIN_1 7
#define MOTOR_B_PIN_2 8

// Line Follower Configuration
#define INPUT_SIZE 3
#define CATEGORY_COUNT 2
#define VIGILANCE 0.9

ARTLibrary art(VIGILANCE, INPUT_SIZE, CATEGORY_COUNT);

void setup() {
  // Configure line sensors
  pinMode(IR_PIN_1, INPUT);
  pinMode(IR_PIN_2, INPUT);
  pinMode(IR_PIN_3, INPUT);

  // Configure motor driver pins
  pinMode(MOTOR_A_PIN_1, OUTPUT);
  pinMode(MOTOR_A_PIN_2, OUTPUT);
  pinMode(MOTOR_B_PIN_1, OUTPUT);
  pinMode(MOTOR_B_PIN_2, OUTPUT);
}

void loop() {
  // Read line sensor values
  int lineSensor1 = digitalRead(IR_PIN_1);
  int lineSensor2 = digitalRead(IR_PIN_2);
  int lineSensor3 = digitalRead(IR_PIN_3);

  // Convert line sensor values to input data
  float inputData[INPUT_SIZE];
  inputData[0] = lineSensor1;
  inputData[1] = lineSensor2;
  inputData[2] = lineSensor3;

  // Predict the direction using ART network
  int predictedCategory = art.predict(inputData);

  // Drive the motors based on the predicted direction
  if (predictedCategory == 0) {  // Left
    driveMotors(LOW, HIGH, HIGH, LOW);
  } else if (predictedCategory == 1) {  // Right
    driveMotors(HIGH, LOW, LOW, HIGH);
  }

  delay(100);
}

void driveMotors(int motorAPin1, int motorAPin2, int motorBPin1, int motorBPin2) {
  digitalWrite(MOTOR_A_PIN_1, motorAPin1);
  digitalWrite(MOTOR_A_PIN_2, motorAPin2);
  digitalWrite(MOTOR_B_PIN_1, motorBPin1);
  digitalWrite(MOTOR_B_PIN_2, motorBPin2);
}
