#ifndef ART_h
#define ART_h

#include <Arduino.h>

class ART {
public:
    ART(int inputSize, int prototypeSize, float vigilance);

    void initialize(float* input);
    void train(float* input);
    int classify(float* input);

private:
    int inputSize;
    int prototypeSize;
    float vigilance;

    float* prototypes;
    bool* categoryTaken;
};

#endif
