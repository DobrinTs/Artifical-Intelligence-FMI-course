#include<iostream>
#include<stack>
#include<set>;
using namespace std;
using coordinates = pair<int, int>;

bool traverse(char** arr, int N, coordinates crr, coordinates goal, set<coordinates>& visited)
{
    visited.insert(crr);
    if(crr.first == goal.first && crr.second == goal.second)
    {
        arr[crr.first][crr.second] = '*';
        return true;
    }

    coordinates next;
    for(int i=1; i>=-1; i=i-2)
    {

        next.first = crr.first + i;
        next.second = crr.second;

        if(next.first >= 0 && next.first < N
                && next.second >=0 && next.second < N
                && !visited.count(next) && arr[next.first][next.second] == '1')
        {
            if(traverse(arr, N, next, goal, visited) )
            {
                arr[crr.first][crr.second] = '*';
                return true;
            }
        }

    }

    for(int j=1; j>=-1; j=j-2)
    {
        next.first = crr.first ;
        next.second = crr.second + j;

        if(next.first >= 0 && next.first < N
                && next.second >=0 && next.second < N
                && !visited.count(next)  && arr[next.first][next.second] == '1')
        {
            if(traverse(arr, N, next, goal, visited) )
            {
                arr[crr.first][crr.second] = '*';
                return true;
            }
        }
    }

    return false;
}

int main()
{
    int N, k;
    cout<<"Enter N: ";
    cin>>N;
    while(N<6 || N>9)
    {
        cout<<"N should be in the interval (5, 10)! Enter new value for N: ";
        cin>>N;
    }

    cout<<"Enter k: ";
    cin>>k;
    while(k<0 || k>N*N)
    {
        cout<<"k should be in the interval [0, N*N]! Enter new value for k: ";
        cin>>k;
    }

    char** arr = new char*[N];

    for(int i=0; i<N; i++)
    {
        arr[i] = new char[N];
        for(int j=0; j<N; j++)
        {
            arr[i][j] = '1';
        }
    }

    int row, col;
    for(int i=0; i < k; i++)
    {
        cout<<"Enter unpassable cell coordinates: ";
        cin>>row>>col;
        arr[row][col] = '0';
    }

    coordinates start, goal;
    cout<<"Enter start: ";
    cin>>start.first>>start.second;

    if(arr[start.first][start.second] == '0') {
        cout<<"Start is an unpassable cell!"<<endl;
        return 0;
    }

    cout<<"Enter goal: ";
    cin>>goal.first>>goal.second;

    set<coordinates> visited;
    bool reached = traverse(arr, N, start, goal, visited);

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout<<endl;
    }

    if(!reached)
    {
        cout<<"Target can not be reached!"<<endl;
    }
    else
    {
        cout<<"Great success!"<<endl;
    }
}
