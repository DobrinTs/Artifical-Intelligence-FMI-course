#ifndef PLANTCLASSPREDICTOR_H
#define PLANTCLASSPREDICTOR_H

#include <vector>
#include <time.h>
#include <stdlib.h>

#include "Perceptron.h"
#include "Plant.h"

class PlantClassPredictor
{
    public:
        PlantClassPredictor();
        virtual ~PlantClassPredictor();

        void train(std::vector<Plant>& trainingDataset);
        std::string predictClass(Plant sample);

        double crossValidate(const std::vector<Plant>& dataset, int numberOfFolds);

    private:
        Perceptron perceptrons[3];
        std::string classNames[3] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

        void restartPerceptrons();
        std::vector<Plant> combineFoldsExceptIdx(std::vector<Plant> folds[],
            int skipFoldIdx, int totalNumberOfFolds);

};

#endif // PLANTCLASSPREDICTOR_H
