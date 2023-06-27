#include "ARTLibrary.h"

#define INPUTS 3
#define CATEGORIES 2
#define VIGILANCE 0.91

ARTLibrary art(VIGILANCE);  // Set the vigilance parameter

// Define pin connections for IR sensors
const int leftSensorPin = 2;
const int centerSensorPin = 3;
const int rightSensorPin = 4;

// Define pin connections for motor driver
const int leftMotorPin1 = 5;
const int leftMotorPin2 = 6;
const int rightMotorPin1 = 7;
const int rightMotorPin2 = 8;

void setup() {
  // Initialize the ART network
  art.initialize(INPUTS, CATEGORIES);  // 3 inputs (sensors), 2 categories (left/right)

  // Set the motor driver pins as outputs
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
}

void loop() {
  // Read sensor values
  int leftSensorValue = digitalRead(leftSensorPin);
  int centerSensorValue = digitalRead(centerSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);

  // Convert sensor values to ART input (0 or 1)
  float input[3] = {static_cast<float>(leftSensorValue),
                    static_cast<float>(centerSensorValue),
                    static_cast<float>(rightSensorValue)};

  // Train the ART network with the input
  art.train(input);

  // Classify the input using the trained network
  int category = art.classify(input);

  // Motor control based on the ART classification
  if (category == 0) {
    // Turn left
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    // Turn right
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
}
