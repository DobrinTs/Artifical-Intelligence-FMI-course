#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<math.h>
using namespace std;

string fullClassName(string classAbbreviation)
{
    if(classAbbreviation == "set")
    {
        return "Iris-setosa";
    }
    else if(classAbbreviation == "ver")
    {
        return "Iris-versicolor";
    }
    else if(classAbbreviation == "vir")
    {
        return "Iris-virginica";
    }
}

struct Plant
{
    double sepalLength;
    double sepalWidth;
    double petalLength;
    double petalWidth;
    string plantClass;

    Plant(double sepalLength,
          double sepalWidth,
          double petalLength,
          double petalWidth,
          string plantClass) : sepalLength(sepalLength), sepalWidth(sepalWidth),
        petalLength(petalLength), petalWidth(petalWidth), plantClass(plantClass) {}

    Plant(const Plant& other) : sepalLength(other.sepalLength), sepalWidth(other.sepalWidth),
        petalLength(other.petalLength), petalWidth(other.petalWidth), plantClass(other.plantClass) {}

    Plant& operator=(const Plant& other)
    {
        if(this!=&other)
        {
            sepalLength=other.sepalLength;
            sepalWidth=other.sepalWidth;
            petalLength=other.petalLength;
            petalWidth=other.petalWidth;
            plantClass=other.plantClass;
        }
        return *this;
    }

    bool operator<(const Plant& other) const //for priority queue of pair<double, Plant>
    {
        int chance = rand() % 10;
        return chance < 5;
    }

    string getPlantClass() const
    {
        return plantClass;
    }

    void print() const
    {
        cout<<sepalLength<<" "<<sepalWidth<<" "<<petalLength<<" "<<petalWidth<<" "<<fullClassName(plantClass)<<endl;
    }
};

string findClassByKNeighbours(const vector<Plant> trainingDataset, Plant newEntry, int k)
{
    priority_queue<pair<double, Plant> > nearestNeighbours;
    double distance;

    for(int i=0; i<trainingDataset.size(); i++)
    {
        distance = sqrt(
                       (newEntry.petalLength - trainingDataset[i].petalLength)*(newEntry.petalLength - trainingDataset[i].petalLength) +
                       (newEntry.petalWidth - trainingDataset[i].petalWidth)*(newEntry.petalWidth - trainingDataset[i].petalWidth) +
                       (newEntry.sepalLength - trainingDataset[i].sepalLength)*(newEntry.sepalLength - trainingDataset[i].sepalLength) +
                       (newEntry.sepalWidth - trainingDataset[i].sepalWidth)*(newEntry.sepalWidth - trainingDataset[i].sepalWidth)

                   );
        if(nearestNeighbours.size() < k)
        {
            nearestNeighbours.push(pair<double, Plant>(distance, trainingDataset[i]));
        }
        else if(nearestNeighbours.top().first > distance)
        {
            nearestNeighbours.pop();
            nearestNeighbours.push(pair<double, Plant>(distance, trainingDataset[i]));
        }
    }

    int irisSetosa = 0, irisVersicolor = 0, irisVirginica = 0;
    string nearestNeighbourClass;
    while(!nearestNeighbours.empty())
    {
        string topClass = nearestNeighbours.top().second.getPlantClass();
        if(nearestNeighbours.size() == 1)
        {
            nearestNeighbourClass = topClass;
        }

        if( topClass == "set")
        {
            irisSetosa++;
        }
        else if(topClass == "ver")
        {
            irisVersicolor++;
        }
        else if( topClass == "vir")
        {
            irisVirginica++;
        }

        nearestNeighbours.pop();
    }

    string maxCountClass = "set";
    int maxCount = irisSetosa;

    if(irisVersicolor > maxCount || (irisVersicolor == maxCount && nearestNeighbourClass == "ver"))
    {
        maxCountClass = "ver";
        maxCount = irisVersicolor;
    }

    if(irisVirginica > maxCount || (irisVirginica == maxCount && nearestNeighbourClass == "vir"))
    {
        maxCountClass = "vir";
        maxCount = irisVirginica;
    }

    return maxCountClass;
}

void kNN()
{
    ifstream file ("iris.txt", std::ifstream::in);
    double sL, sW, pL, pW;
    string pC;

    vector<Plant> trainingDataset;
    vector<Plant> testDataset;
    while(file>>sL)
    {
        file.ignore(1);
        file>>sW;
        file.ignore(1);
        file>>pL;
        file.ignore(1);
        file>>pW;
        file.ignore(1);
        getline(file, pC);
        pC = pC.substr(5, 3);

        trainingDataset.push_back(Plant(sL, sW, pL, pW, pC));
    }

    while(testDataset.size() < 20)
    {
        int idx = rand() % trainingDataset.size();
        testDataset.push_back(trainingDataset[idx]);
        trainingDataset.erase(trainingDataset.begin()+idx);
    }

    int k;
    cout<<"Enter k: ";
    cin>>k;

    int correctCount = 0;
    for(int i=0; i<testDataset.size(); i++) {
        cout<<"Test dataset individual info: "<<endl;
        testDataset[i].print();
        cout<<"Predicted class: ";
        string predictionResult = findClassByKNeighbours(trainingDataset, testDataset[i], k);
        cout<<fullClassName(predictionResult)<<endl;
        cout<<"------------------"<<endl;

        if(testDataset[i].getPlantClass() == predictionResult) {
            correctCount++;
        }
    }

    double accuracy = (double)correctCount/testDataset.size();

    cout<<"Accuracy: "<< accuracy;
}

int main()
{
    srand (time(NULL));
    kNN();
}
