#include "ARTLibrary.h"

ARTLibrary::ARTLibrary(float vigilance) {
  this->vigilance = vigilance;
}

void ARTLibrary::initialize(int inputSize, int categorySize) {
  numInputs = inputSize;
  numCategories = categorySize;

  // Initialize the weights and activations to zero
  for (int i = 0; i < numCategories; i++) {
    for (int j = 0; j < numInputs; j++) {
      weights[i][j] = 0.0;
    }
    activations[i] = 0.0;
  }
}

void ARTLibrary::train(float input[MAX_INPUT_SIZE]) {
  // Find the category with the highest activation
  int winner = 0;
  float maxActivation = 0.0;

  for (int i = 0; i < numCategories; i++) {
    float dotProduct = 0.0;
    float inputMagnitude = 0.0;
    float weightMagnitude = 0.0;

    // Calculate the dot product and magnitudes
    for (int j = 0; j < numInputs; j++) {
      dotProduct += weights[i][j] * input[j];
      inputMagnitude += input[j] * input[j];
      weightMagnitude += weights[i][j] * weights[i][j];
    }

    // Calculate the activation
    float activation = dotProduct / (sqrt(inputMagnitude) + sqrt(weightMagnitude));

    // Update the winner if the activation is higher
    if (activation > maxActivation) {
      maxActivation = activation;
      winner = i;
    }

    activations[i] = activation;
  }

  // Check if the winner meets the vigilance criterion
  float inputMagnitude = 0.0;
  for (int i = 0; i < numInputs; i++) {
    inputMagnitude += input[i] * input[i];
  }

  float similarity = maxActivation / sqrt(inputMagnitude);
  if (similarity >= vigilance) {
    // Update the weights of the winner category
    for (int i = 0; i < numInputs; i++) {
      weights[winner][i] = (weights[winner][i] * activations[winner] + input[i]) / (activations[winner] + 1);
    }
  }
}

int ARTLibrary::classify(float input[MAX_INPUT_SIZE]) {
  // Find the category with the highest activation
  int winner = 0;
  float maxActivation = 0.0;

  for (int i = 0; i < numCategories; i++) {
    float dotProduct = 0.0;
    float inputMagnitude = 0.0;
    float weightMagnitude = 0.0;

    // Calculate the dot product and magnitudes
    for (int j = 0; j < numInputs; j++) {
      dotProduct += weights[i][j] * input[j];
      inputMagnitude += input[j] * input[j];
      weightMagnitude += weights[i][j] * weights[i][j];
    }

    // Calculate the activation
    float activation = dotProduct / (sqrt(inputMagnitude) + sqrt(weightMagnitude));

    // Update the winner if the activation is higher
    if (activation > maxActivation) {
      maxActivation = activation;
      winner = i;
    }

    activations[i] = activation;
  }

  return winner;
}
