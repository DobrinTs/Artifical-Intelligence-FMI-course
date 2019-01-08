#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <assert.h>
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

    int maxLearnIterations = 150;

    double sigmoid(double x);
    double sigmoidD(double x);
    double getInputWeightProduct(const std::vector<double>& inputs);
    double trySampleAndGetError(const std::vector<double> &inputs, double expectedResult);
};

#endif // PERCEPTRON_H
