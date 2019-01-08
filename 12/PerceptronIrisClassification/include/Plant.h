#ifndef PLANT_H
#define PLANT_H

#include<iostream>
#include<vector>

class Plant
{
public:
    double sepalLength;
    double sepalWidth;
    double petalLength;
    double petalWidth;
    std::string plantClass;

    std::vector<double> getMeasurementVector() const {
        std::vector<double> measurements;
        measurements.push_back(sepalLength);
        measurements.push_back(sepalWidth);
        measurements.push_back(petalLength);
        measurements.push_back(petalWidth);
        return measurements;
    }

    void print() const
    {
        std::cout<< sepalLength<<" "<<sepalWidth<<" "<<
                 petalLength<<" "<<petalWidth<<" "<<plantClass<<std::endl;
    }
};

#endif // PLANT_H
