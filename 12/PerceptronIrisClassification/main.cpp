#include <iostream>
#include <fstream>
#include<string.h>

#include "Plant.h"
#include "Perceptron.h"
#include "PlantClassPredictor.h"

using namespace std;

vector<Plant> readDataFromFile(string filename) {
    ifstream file (filename, ifstream::in);
    vector<Plant> result;
    Plant p;

    while(file>>p.sepalLength)
    {
        file.ignore(1);
        file>>p.sepalWidth;
        file.ignore(1);
        file>>p.petalLength;
        file.ignore(1);
        file>>p.petalWidth;
        file.ignore(1);
        string plantClass;
        getline(file, p.plantClass);
        p.plantClass = p.plantClass.substr(0, p.plantClass.length() - 1);

        result.push_back(p);
    }
    return result;
}

int main()
{
    int n;
    cout<<"Enter number of folds: ";
    cin>>n;
    vector<Plant> dataset = readDataFromFile("iris.txt");
    PlantClassPredictor predictor;

    double meanAccuracy = predictor.crossValidate(dataset, n);
    cout<<"Mean accuracy is: "<<meanAccuracy;
}
