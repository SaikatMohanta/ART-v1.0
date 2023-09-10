#include <Arduino.h>
#include "ART.h"

// Define the input size and prototype size
const int inputSize = 2;
const int prototypeSize = 5;

// Define the vigilance parameter (between 0 and 1)
const float vigilance = 0.7;

// Create an instance of the ART network
ART art(inputSize, prototypeSize, vigilance);

void setup() {
    Serial.begin(9600);
    
    // Initialize the ART network with some sample data
    float sample1[inputSize] = {0.1, 0.2};
    float sample2[inputSize] = {0.8, 0.9};
    float sample3[inputSize] = {0.3, 0.4};

    art.initialize(sample1);
    art.initialize(sample2);
    art.initialize(sample3);
}

void loop() {
    // Input data to classify
    float input[inputSize] = {0.789, 0.899};

    // Classify the input data
    int category = art.classify(input);

    Serial.print("Input belongs to category: ");
    Serial.println(category);

    delay(1000);
}

