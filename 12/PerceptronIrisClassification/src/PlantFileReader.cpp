#include "PlantFileReader.h"

PlantFileReader::PlantFileReader(std::string filename)
{
    file.open(filename, std::ifstream::in);
}

PlantFileReader::~PlantFileReader() {}

std::vector<Plant> PlantFileReader::getPlants() {
    std::vector<Plant> result;
    while(file.peek() != EOF)
    {
        Plant p = readPlantFromStream();
        result.push_back(p);
    }

    return result;
}

Plant PlantFileReader::readPlantFromStream() {
    Plant p;
    file>>p.sepalLength;
    file.ignore(1);
    file>>p.sepalWidth;
    file.ignore(1);
    file>>p.petalLength;
    file.ignore(1);
    file>>p.petalWidth;
    file.ignore(1);
    getline(file, p.plantClass);

    return p;
}


