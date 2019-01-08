#ifndef PLANTFILEREADER_H
#define PLANTFILEREADER_H

#include <string>
#include <fstream>
#include <vector>

#include "Plant.h"

class PlantFileReader
{
    public:
        PlantFileReader(std::string filename);
        virtual ~PlantFileReader();

        std::vector<Plant> getPlants();

    private:
        std::ifstream file;

        Plant readPlantFromStream();
};

#endif // PLANTFILEREADER_H
