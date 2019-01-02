#include<iostream>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <fstream>

using namespace std;

struct Item
{
    string name;
    int weight;
    int value;

    Item(string name, int weight, int value) : name(name), weight(weight), value(value) {}

    void print() const
    {
        cout<<"Name: "<<name<<"; weight: "<<weight<<"; value: "<<value<<endl;
    }
};

struct Knapsack
{
    bool* takenItems;
    int totalValue;
    int totalWeight;
    int maxWeight;
    int N;

    Knapsack(int N, int maxWeight) : N(N), maxWeight(maxWeight)
    {
        takenItems = new bool[N];
        for(int i=0; i<N; i++)
        {
            takenItems[i]=false;
        }
        totalValue = 0;
        totalWeight = 0;
    }

    Knapsack(const Knapsack& other) : N(other.N), totalValue(other.totalValue),
        totalWeight(other.totalWeight), maxWeight(other.maxWeight)
    {
        takenItems = new bool[N];
        for(int i=0; i<N; i++)
        {
            takenItems[i]=other.takenItems[i];
        }
    }

    Knapsack& operator=(const Knapsack& other)
    {
        if(this!=&other)
        {
            delete[] takenItems;
            this->N = other.N;
            takenItems = new bool[this->N];
            for(int i=0; i<this->N; i++)
            {
                this->takenItems[i]=other.takenItems[i];
            }
            this->totalValue = other.totalValue;
            this->totalWeight = other.totalWeight;
            this->maxWeight = other.maxWeight;
        }
        return *this;
    }

    ~Knapsack()
    {
        delete[] takenItems;
    }

    void chanceMutate(const vector<Item>& items)
    {
        int chance = rand() % 5; // mutates only if chance == 1
        if(chance == 1)
        {
            int randomIndex = rand() % N;

            if(takenItems[randomIndex] == true) // if item was taken remove it
            {
                takenItems[randomIndex] = false;
                totalValue -= items[randomIndex].value;
                totalWeight -= items[randomIndex].weight;
            }
            else // if item wasnt taken check if we won't surpass maxWeigth and then take it
            {
                if(totalWeight + items[randomIndex].weight > maxWeight)
                {
                    return;
                }
                else
                {
                    takenItems[randomIndex] = true;
                    totalValue += items[randomIndex].value;
                    totalWeight += items[randomIndex].weight;
                }
            }

        }
    }

    void initialRandomize(const vector<Item>& items, int N)
    {
        int initialPopCount = N/3; //could be less if rand generates same values or if we fill the knapsack
        for(int i=0; i<initialPopCount; i++)
        {
            int index = rand() % N;
            if(takenItems[index] == false && (totalWeight + items[i].weight <= maxWeight) )
            {
                takenItems[index] = true;
                totalValue += items[i].value;
                totalWeight += items[i].weight;
            }
        }
    }

    void print(const vector<Item>& items)
    {
        for(int i=0; i<N; i++)
        {
            cout<<takenItems[i]<<" ";
        }
        cout<<endl<<"Total value: "<<totalValue<<endl;
        cout<<"Total weight: "<<totalWeight<<endl;
        cout<<"Taken items:"<<endl;
        for(int i=0; i<N; i++)
        {
            if(takenItems[i])
            {
                items[i].print();
            }
        }
    }
};

struct less_than_value
{
    inline bool operator() (const Knapsack& k1, const Knapsack& k2)
    {
        return (k1.totalValue > k2.totalValue);
    }
};

Knapsack crossover(const vector<Item>& items, const Knapsack& parent1, const Knapsack& parent2)
{
    Knapsack child(parent1.N, parent1.maxWeight);
    int separator = rand() % (child.N - 2) + 1;
    for(int i=0; i<child.N; i++)
    {
        if(i<separator)
        {
            if(parent1.takenItems[i] == true)
            {
                child.takenItems[i] = true;
                child.totalValue += items[i].value;
                child.totalWeight += items[i].weight;
            }
        }
        else
        {
            if(parent2.takenItems[i] == true)
            {
                child.takenItems[i] = true;
                child.totalValue += items[i].value;
                child.totalWeight += items[i].weight;
            }
        }
    }

    while(child.totalWeight > child.maxWeight)
    {
        int toRemoveIndex = rand() % child.N;
        if(child.takenItems[toRemoveIndex] == true)
        {
            child.takenItems[toRemoveIndex] = false;
            child.totalValue -= items[toRemoveIndex].value;
            child.totalWeight -= items[toRemoveIndex].weight;
        }
    }

    return child;
}

void knapsackProblem(const vector<Item>& items, int N, int maxWeight)
{
    int populationSize = N*5;
    vector<Knapsack> population;

    for(int i=0; i<populationSize; i++)
    {
        Knapsack newKnapsack(N, maxWeight);
        newKnapsack.initialRandomize(items, N);
        population.push_back(newKnapsack);
    }

    int numberOfIterations = populationSize/2;
    for(int iter=0; iter<numberOfIterations; iter++)
    {
        for(int i=0; i<populationSize/3; i++)
        {
            for(int j=i+1; j<populationSize/3; j++)
            {
                Knapsack successor = crossover(items, population[i], population[j]);
                successor.chanceMutate(items);

                population.push_back(successor);
            }
        }

        sort(population.begin(), population.end(), less_than_value());

        while(population.size() > populationSize)
        {
            population.pop_back();
        }
    }
    population[0].print(items);
}

int main()
{
    srand (time(NULL));
    vector<Item> items;

    ifstream ifs ("items.txt", ifstream::in);
    string name;
    int weight, value;
    while(ifs>>name)
    {
        ifs>>weight;
        ifs>>value;
        items.push_back(Item(name, weight, value));

    }


    int N = items.size();

    knapsackProblem(items, N, 5000);
}
