#ifndef ARTLibrary_h
#define ARTLibrary_h

#include <Arduino.h>

#define MAX_INPUT_SIZE 10
#define MAX_CATEGORY_SIZE 10

class ARTLibrary {
public:
  ARTLibrary(float vigilance);

  void initialize(int inputSize, int categorySize);
  void train(float input[MAX_INPUT_SIZE]);
  int classify(float input[MAX_INPUT_SIZE]);

private:
  float vigilance;
  float weights[MAX_CATEGORY_SIZE][MAX_INPUT_SIZE];
  float activations[MAX_CATEGORY_SIZE];
  int numCategories;
  int numInputs;
};

#endif
