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

double PlantClassPredictor::crossValidate(const std::vector<Plant>& dataset, int numberOfFolds)
{
    srand(time(NULL));

    std::vector<Plant> folds[numberOfFolds];
    for(Plant p : dataset)
    {
        int foldIdx = rand() % numberOfFolds;
        folds[foldIdx].push_back(p);
    }

    double meanAccuracy = 0;
    for(int i=0; i<numberOfFolds; i++) {
        restartPerceptrons();
        std::vector<Plant> trainingDataset = combineFoldsExceptIdx(folds, i, numberOfFolds);
        train(trainingDataset);

        int correctCount = 0;
        for(int j=0; j<folds[i].size(); j++)
        {
            std::string prediction = predictClass(folds[i][j]);
            if(prediction == folds[i][j].plantClass)
            {
                correctCount++;
            }
        }
        double accuracy = (double)correctCount/folds[i].size();
        meanAccuracy += accuracy;
    }
    meanAccuracy /= numberOfFolds;
    return meanAccuracy;
}

std::vector<Plant> PlantClassPredictor::combineFoldsExceptIdx(std::vector<Plant> folds[],
    int skipFoldIdx, int totalNumberOfFolds)
{
    std::vector<Plant> combined;

    for(int i=0; i<totalNumberOfFolds; i++)
    {
        if(i == skipFoldIdx)
        {
            continue;
        }

        for(int j=0; j<folds[i].size(); j++)
        {
            combined.push_back(folds[i][j]);
        }
    }
    return combined;
}
