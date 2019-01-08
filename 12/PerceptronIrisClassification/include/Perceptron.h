#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

#include "Plant.h"

class Perceptron
{
public:
    Perceptron();
    virtual ~Perceptron();

    double getResult(const std::vector<double>& inputs);
    void train(std::vector<Plant>& trainingSet, std::string targetPlantClass);
    void randomizeWeights();

private:
    double bias;
    double biasWeight;
    double learnRate = 0.1;
    std::vector<double> weights;

    int MAX_LEARN_ITERATIONS = 150;
    int NUMBER_OF_INPUTS = 4;
    double ACCEPTABLE_ERROR = 0.075;

    double sigmoid(double x);
    double sigmoidDerivative(double x);
    double getInputWeightProduct(const std::vector<double>& inputs);
    double learnSampleAndGetError(const std::vector<double> &inputs, double expectedResult);
};

#endif // PERCEPTRON_H
