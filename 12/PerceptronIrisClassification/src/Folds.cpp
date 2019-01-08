#include "Folds.h"

Folds::Folds(const std::vector<Plant>& dataset, int numberOfFolds)
{
    srand(time(NULL));
    folds.resize(numberOfFolds);
    for(Plant p : dataset)
    {
        int foldIdx = rand() % numberOfFolds;
        folds[foldIdx].push_back(p);
    }
}

Folds::~Folds()
{}

std::vector<Plant> Folds::getCombinedFoldsExceptIdx(int idx) {
    std::vector<Plant> result;
    for(int i=0; i<folds.size(); i++) {
        if(i == idx) {
            continue;
        }

        result.insert(result.end(), folds[i].begin(), folds[i].end());
    }

    return result;
}

std::vector<Plant> Folds::getFold(int idx) {
    return folds[idx];
}

