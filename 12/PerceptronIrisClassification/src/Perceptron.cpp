#include "Perceptron.h"

Perceptron::Perceptron()
    : bias(1)
{
    randomizeWeights();
}

Perceptron::~Perceptron()
{}

void Perceptron::randomizeWeights() {
    weights.clear();
    srand(time(NULL));
    double r;
    for(int i=0; i<4; i++)
    {
        r = ((double) rand() / (RAND_MAX)) - 0.5;
        weights.push_back(r);
    }
    biasWeight = ((double) rand() / (RAND_MAX)) - 0.5;
}

void Perceptron::train(std::vector<Plant>& trainingSet, std::string targetPlantClass)
{
    random_shuffle(trainingSet.begin(), trainingSet.end());
    for(int iterations = 0; iterations < maxLearnIterations; iterations++ )
    {
        int errorCount = 0;
        for (const Plant &p : trainingSet)
        {
            double expectedResult = p.plantClass == targetPlantClass ? 1.0 : 0.0;
            double error = trySampleAndGetError(p.getMeasurementVector(), expectedResult);

            if(error > 0.075)
            {
                errorCount++;
            }
        }
        if(errorCount == 0)
        {
            break;
        }
    }
}

double Perceptron::trySampleAndGetError(const std::vector<double> &inputs, double expectedResult )
{
    double product = getInputWeightProduct(inputs);
    double sigDFromProduct = sigmoidD(product);
    double result = getResult(inputs);
    double error = expectedResult - result;

    for (int i = 0; i < weights.size(); i++)
    {
        weights[i] += learnRate * error * inputs[i] * sigDFromProduct;
    }
    biasWeight += learnRate * error * bias * sigDFromProduct;

    return error;
}

double Perceptron::getInputWeightProduct(const std::vector<double>& inputs)
{
    assert(inputs.size() == weights.size());

    double product = 0;
    for(int i=0; i<inputs.size(); i++)
    {
        product += inputs[i] * weights[i];
    }
    product += bias * biasWeight;

    return product;
}

double Perceptron::getResult(const std::vector<double>& inputs)
{
    assert(inputs.size() == weights.size());
    double product = getInputWeightProduct(inputs);

    return sigmoid(product);
}

double Perceptron::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double Perceptron::sigmoidD(double x)
{
    return exp(-x) / ( (1 + exp(-x)) * (1 + exp(-x)) );
}

