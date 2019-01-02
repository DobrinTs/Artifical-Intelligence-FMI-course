#include<iostream>
#include<fstream>
#include <math.h>
#include<vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Politician
{
    string className;
    char* attributes;

    Politician()
    {
        className = "unknown";
        attributes = new char[16];
    }

    ~Politician()
    {
        delete [] attributes;
    }

    Politician(const Politician& other) : className(other.className)
    {
        attributes = new char[16];
        for(int i=0; i<16; i++)
        {
            attributes[i] = other.attributes[i];
        }
    }

    Politician& operator=(const Politician& other)
    {
        if(this!=&other)
        {
            className=other.className;
            for(int i=0; i<16; i++)
            {
                attributes[i] = other.attributes[i];
            }
        }
        return *this;
    }

    void print()
    {
        cout<<className<<",";
        for(int i=0; i<16; i++)
        {
            cout<<attributes[i]<<",";
        }
        cout<<endl;
    }
};

vector<Politician> readData()
{
    ifstream file ("house-votes-84.data", std::ifstream::in);
    string line;

    vector<Politician> politicians;
    while(file>>line)
    {
        Politician newEntry;
        bool questionMark = false;
        int idx = line.find(',');
        newEntry.className = line.substr(0, idx);
        for(int i=0; i<16; i++)
        {
            if(line[idx + 1 + 2*i] == '?')
            {
                questionMark = true;
                break;
            }
            newEntry.attributes[i] = line[idx + 1 + 2*i];
        }
        if(questionMark == true)
        {
            continue;
        }
        politicians.push_back(newEntry);
    }
    return politicians;
}

double naiveBayesClassifier (vector<Politician> folds[10], int trainingFoldIdx)
{
    int republicanCount = 2;
    int democratCount = 2;
    double attributeFrequencies[16][4]; // columns: yes-republican, no-republican, yes-democrat, no-democrat
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<4; j++)
        {
            attributeFrequencies[i][j] = 1;
        }
    }

    for(int foldIdx = 0; foldIdx<10; foldIdx++)
    {
        if(foldIdx == trainingFoldIdx) continue;

        for(int j=0; j<folds[foldIdx].size(); j++)
        {
            Politician crr = folds[foldIdx][j];
            if(crr.className == "republican")
            {
                republicanCount++;
            }
            else if(crr.className == "democrat")
            {
                democratCount++;
            }

            for(int i=0; i<16; i++)
            {
                if(crr.className == "republican")
                {
                    if(crr.attributes[i] == 'y')
                    {
                        attributeFrequencies[i][0]++;
                    }
                    else if(crr.attributes[i] == 'n')
                    {
                        attributeFrequencies[i][1]++;
                    }
                }
                else if(crr.className == "democrat")
                {
                    if(crr.attributes[i] == 'y')
                    {
                        attributeFrequencies[i][2]++;
                    }
                    else if(crr.attributes[i] == 'n')
                    {
                        attributeFrequencies[i][3]++;
                    }
                }
            }
        }
    }

    for(int i=0; i<16; i++)
    {
        attributeFrequencies[i][0] /= republicanCount;
        attributeFrequencies[i][1] /= republicanCount;
        attributeFrequencies[i][2] /= democratCount;
        attributeFrequencies[i][3] /= democratCount;
    }

    /*for(int i=0; i<16; i++) {
        for(int j=0; j<4; j++){
            cout<<attributeFrequencies[i][j]<<"; ";
        }
        cout<<endl;
    }*/

    int correctPredictions = 0;
    for(int i=0; i<folds[trainingFoldIdx].size(); i++)
    {
        Politician crr = folds[trainingFoldIdx][i];
        double pRepublican = log( (double)republicanCount / (republicanCount+democratCount) );
        double pDemocrat = log ( (double)democratCount / (republicanCount+democratCount) );

        for(int j=0; j<16; j++)
        {
            if(crr.attributes[j] == 'y')
            {
                pRepublican += log(attributeFrequencies[j][0]);
                pDemocrat += log(attributeFrequencies[j][2]);
            }
            else if(crr.attributes[j] == 'n')
            {
                pRepublican += log(attributeFrequencies[j][1]);
                pDemocrat += log(attributeFrequencies[j][3]);
            }
        }

        if(pRepublican > pDemocrat)
        {
            //predicted republican
            if(crr.className == "republican")
            {
                correctPredictions++;
            }
        }
        else
        {
            //predicted democrat
            if(crr.className == "democrat")
            {
                correctPredictions++;
            }
        }
    }
    return (double)correctPredictions/folds[trainingFoldIdx].size();
}

int main()
{
    srand (time(NULL));
    vector<Politician> politicians = readData();
    vector<Politician> folds[10];

    for(int i=0; i<politicians.size(); i++)
    {
        int randomIdx = rand() % 10;
        folds[randomIdx].push_back(politicians[i]);
    }
    double accuracies[10];
    double meanAccuracy = 0;

    for(int i=0; i<10; i++)
    {
        accuracies[i] = naiveBayesClassifier(folds, i);
        meanAccuracy += accuracies[i];
        cout<<"Accuracy when testing on fold "<<i<<" is: "<<accuracies[i]<<endl;
    }
    meanAccuracy/=10;
    cout<<"Mean accuracy is: "<<meanAccuracy<<endl;
}
