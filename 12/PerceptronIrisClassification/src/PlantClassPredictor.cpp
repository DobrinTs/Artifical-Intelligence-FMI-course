#include "PlantClassPredictor.h"

PlantClassPredictor::PlantClassPredictor()
{}

PlantClassPredictor::~PlantClassPredictor()
{}

void PlantClassPredictor::train(std::vector<Plant>& trainingDataset)
{
    for(int i=0; i<3; i++)
    {
        perceptrons[i].train(trainingDataset, classNames[i]);
    }
}

std::string PlantClassPredictor::predictClass(Plant sample)
{
    double perceptronsResults[3];
    for(int i=0; i<3; i++)
    {
        perceptronsResults[i] = perceptrons[i].getResult(sample.getMeasurementVector());
    }

    if(perceptronsResults[0] >= perceptronsResults[1]
            && perceptronsResults[0] >= perceptronsResults[2])
    {
        return classNames[0];
    }
    else if(perceptronsResults[1] >= perceptronsResults[2])
    {
        return classNames[1];
    }
    else
    {
        return classNames[2];
    }
}

void PlantClassPredictor::restartPerceptrons() {
    for(int i=0; i<3; i++) {
        perceptrons[i].randomizeWeights();
    }
}

double PlantClassPredictor::crossValidate(const std::vector<Plant>& dataset, const int numberOfFolds)
{
    Folds folds(dataset, numberOfFolds);

    double meanAccuracy = 0;
    for(int i=0; i<numberOfFolds; i++) {
        std::vector<Plant> trainingDataset = folds.getCombinedFoldsExceptIdx(i);
        std::vector<Plant> testDataset = folds.getFold(i);

        restartPerceptrons();
        train(trainingDataset);

        int correctCount = 0;
        for(int j=0; j<testDataset.size(); j++)
        {
            std::string prediction = predictClass(testDataset[j]);
            if(prediction == testDataset[j].plantClass)
            {
                correctCount++;
            }
        }
        double accuracy = (double)correctCount/testDataset.size();
        meanAccuracy += accuracy;
    }
    meanAccuracy /= numberOfFolds;
    return meanAccuracy;

}
