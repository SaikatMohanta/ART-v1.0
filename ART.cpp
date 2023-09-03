#include "ART.h"

ART::ART(int inputSize, int prototypeSize, float vigilance) {
    this->inputSize = inputSize;
    this->prototypeSize = prototypeSize;
    this->vigilance = vigilance;

    prototypes = new float[inputSize * prototypeSize];
    categoryTaken = new bool[prototypeSize];

    // Initialize prototypes and categoryTaken arrays
    for (int i = 0; i < prototypeSize; i++) {
        categoryTaken[i] = false;
        for (int j = 0; j < inputSize; j++) {
            prototypes[i * inputSize + j] = 0.0;
        }
    }
}

void ART::initialize(float* input) {
    // Find an uncommitted category for the input
    int uncommittedCategory = -1;
    for (int i = 0; i < prototypeSize; i++) {
        if (!categoryTaken[i]) {
            uncommittedCategory = i;
            break;
        }
    }

    if (uncommittedCategory != -1) {
        // Assign the input to the uncommitted category
        categoryTaken[uncommittedCategory] = true;
        for (int j = 0; j < inputSize; j++) {
            prototypes[uncommittedCategory * inputSize + j] = input[j];
        }
    }
}

void ART::train(float* input) {
    // Find the category with the highest match to the input
    int winningCategory = -1;
    float maxResponse = -1.0;

    for (int i = 0; i < prototypeSize; i++) {
        if (categoryTaken[i]) {
            float dotProduct = 0.0;
            float inputNorm = 0.0;
            float prototypeNorm = 0.0;

            for (int j = 0; j < inputSize; j++) {
                dotProduct += input[j] * prototypes[i * inputSize + j];
                inputNorm += input[j] * input[j];
                prototypeNorm += prototypes[i * inputSize + j] * prototypes[i * inputSize + j];
            }

            float response = dotProduct / (sqrt(inputNorm) * sqrt(prototypeNorm));

            if (response > maxResponse) {
                maxResponse = response;
                winningCategory = i;
            }
        }
    }

    if (maxResponse >= vigilance) {
        // Update the winning category
        for (int j = 0; j < inputSize; j++) {
            prototypes[winningCategory * inputSize + j] =
                input[j] * vigilance + prototypes[winningCategory * inputSize + j] * (1 - vigilance);
        }
    } else {
        // Create a new category
        initialize(input);
    }
}

int ART::classify(float* input) {
    // Find the category with the highest match to the input
    int winningCategory = -1;
    float maxResponse = -1.0;

    for (int i = 0; i < prototypeSize; i++) {
        if (categoryTaken[i]) {
            float dotProduct = 0.0;
            float inputNorm = 0.0;
            float prototypeNorm = 0.0;

            for (int j = 0; j < inputSize; j++) {
                dotProduct += input[j] * prototypes[i * inputSize + j];
                inputNorm += input[j] * input[j];
                prototypeNorm += prototypes[i * inputSize + j] * prototypes[i * inputSize + j];
            }

            float response = dotProduct / (sqrt(inputNorm) * sqrt(prototypeNorm));

            if (response > maxResponse) {
                maxResponse = response;
                winningCategory = i;
            }
        }
    }

    return winningCategory;
}
