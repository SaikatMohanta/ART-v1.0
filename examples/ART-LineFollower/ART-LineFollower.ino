#include <ART.h>

// Define ART parameters
const int inputSize = 3;  // Three proximity sensors
const int prototypeSize = 2;  // Two categories: On the line and Off the line
const float vigilance = 0.8;

// Create an instance of the ART network
ART art(inputSize, prototypeSize, vigilance);

// Define sensor pins
const int sensorLeftPin = 2;
const int sensorCenterPin = 3;
const int sensorRightPin = 4;

// Define motor pins
const int leftMotor1 = 5;
const int leftMotor2 = 6;
const int rightMotor1 = 7;
const int rightMotor2 = 8;

// Sensor thresholds
const int sensorThreshold = 500;  // Adjust this threshold for your sensors

void setup() {
  // Initialize sensors as inputs
  pinMode(sensorLeftPin, INPUT);
  pinMode(sensorCenterPin, INPUT);
  pinMode(sensorRightPin, INPUT);

  // Initialize motors as outputs
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  // Initialize the ART network
  float onLine[inputSize] = {0.0, 0.0, 0.0};
  float offLine[inputSize] = {1.0, 1.0, 1.0};

  art.initialize(onLine);    // Initialize category for "On the line"
  art.initialize(offLine);   // Initialize category for "Off the line"
}

void loop() {
  // Read sensor values
  int leftSensorValue = digitalRead(sensorLeftPin);
  int centerSensorValue = digitalRead(sensorCenterPin);
  int rightSensorValue = digitalRead(sensorRightPin);

  // Create input vector for the ART network
  float input[inputSize] = {float(leftSensorValue), float(centerSensorValue), float(rightSensorValue)};

  // Classify sensor readings
  int category = art.classify(input);

  // Perform actions based on the category
  if (category == 0) {  // "On the line"
    // Forward motion
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  } else if (category == 1) {  // "Off the line"
    // Turn left
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }

  // Delay to control the speed of the robot
  delay(100);
}
