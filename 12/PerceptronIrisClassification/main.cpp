#include <iostream>
#include <fstream>
#include <string.h>

#include "Plant.h"
#include "PlantFileReader.h"
#include "Perceptron.h"
#include "PlantClassPredictor.h"

using namespace std;

int main()
{
    int n;
    cout<<"Enter number of folds: ";
    cin>>n;
    PlantFileReader reader("iris.txt");
    vector<Plant> dataset = reader.getPlants();

    PlantClassPredictor predictor;

    double meanAccuracy = predictor.crossValidate(dataset, n);
    cout<<"Mean accuracy is: "<<meanAccuracy;
}
