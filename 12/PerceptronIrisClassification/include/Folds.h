#ifndef FOLDS_H
#define FOLDS_H

#include <vector>
#include <time.h>
#include <stdlib.h>

#include "Plant.h"

class Folds
{
    public:
        Folds(const std::vector<Plant>& dataset, int numberOfFolds);
        virtual ~Folds();

        std::vector<Plant> getCombinedFoldsExceptIdx(int idx);
        std::vector<Plant> getFold(int idx);
    private:
        std::vector<std::vector<Plant>> folds;

};

#endif // FOLDS_H
