#include "ARTLibrary.h"

ARTLibrary art(0.9);  // Set the vigilance parameter

void setup() {
  // Initialize the ART network
  art.initialize(4, 3);  // Specify the input size and category size
}

void loop() {
  float input[4] = {0.5, 0.3, 0.8, 0.2};

  // Train the ART network with the input
  art.train(input);

  // Classify the input using the trained network
  int category = art.classify(input);

  // Do something with the category result
  // ...
}
