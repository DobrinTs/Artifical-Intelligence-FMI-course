#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

void printBoard(const vector<int>& board, int N)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(board[j] == i)
            {
                cout<<"* ";
            }
            else
            {
                cout<<"_ ";
            }
        }
        cout<<endl;
    }
}

void decreaseConflicts(vector<vector<int> >& conflicts, int N, int row, int col)
{
    for(int j=0; j<N; j++)
    {
        if(j == col)
            continue; //skip own column

        conflicts[row][j]--; //reduce conflicts in same row

        int i1 = row - col + j;
        if(0<=i1 && i1 < N)
        {
            conflicts[i1][j]--; // reduce conflicts in main diagonal
        }

        int i2 = row + col - j;
        if(0 <= i2 && i2 < N)
        {
            conflicts[i2][j]--; // reduce conflicts in secondary diagonal
        }
    }
}

void increaseConflicts(vector<vector<int> >& conflicts, int N, int row, int col)
{
    for(int j=0; j<N; j++)
    {
        if(j == col)
            continue; //skip own column

        conflicts[row][j]++; //increase conflicts in same row

        int i1 = row - col + j;
        if(0<=i1 && i1 < N)
        {
            conflicts[i1][j]++; // increase conflicts in main diagonal
        }

        int i2 = row + col - j;
        if(0 <= i2 && i2 < N)
        {
            conflicts[i2][j]++; // increase conflicts in secondary diagonal
        }
    }
}

void randomizeBoard(vector<int>& board, vector<vector<int> >& conflicts, int N)
{
    for(int j=0; j<N; j++)
    {
        conflicts[j].assign(N, 0);
    }
    random_shuffle ( board.begin(), board.end() );
    for(int j=0; j<N; j++)
    {
        increaseConflicts(conflicts, N, board[j], j);
    }
}

bool hasConflicts(const vector<int>& board, const vector<vector<int> >& conflicts, int N)
{
    for(int j=0; j<N; j++)
    {
        int i = board[j];
        if(conflicts[i][j] != 0)
        {
            return true;
        }
    }
    return false;
}

int getColumnWithMaxConflicts(const vector<int>& board, const vector<vector<int> >& conflicts, int N, int lastCol)
{
    int max = -1;
    int maxCol = -1;
    for(int j=0; j<N; j++)
    {
        int i = board[j];
        if(conflicts[i][j] > max)
        {
            max = conflicts[i][j];
            maxCol = j;
        }
        else if(conflicts[i][j] == max
                && j!=lastCol // don't go in same column as last time
                && (rand() % 10 + 1) > 5)    // random between 1 and 10
        {
            max = conflicts[i][j];
            maxCol = j;
        }
    }
    return maxCol;
}

int getRowWithMinConflicts(const int& col, const vector<vector<int> >& conflicts, int N, int oldRow)
{
    int min = N+1;
    int minRow = N+1;

    for(int i=0; i<N; i++)   //which row in col
    {
        if(conflicts[i][col] < min)
        {
            min = conflicts[i][col];
            minRow = i;
        }
        else if(conflicts[i][col] == min
                &&  i!=oldRow //not same row as before
                && (rand() % 10 + 1) > 5)    // random between 1 and 10
        {
            min = conflicts[i][col];
            minRow = i;
        }
    }

    return minRow;
}

void nQueens(int N)
{
    vector<int> board;
    for(int i=0; i<N; i++)
    {
        board.push_back(i);
    }
    vector<vector<int> > conflicts(N);

    randomizeBoard(board, conflicts, N);

    int MAX_ITER = (2 + N / 2000) * N;
    int oldRow, newRow, oldCol, col=-1;
    int i=0;
    while(i<=MAX_ITER)
    {
        if(i == MAX_ITER)
        {
            randomizeBoard(board, conflicts, N);
            i=0;
        }

        if(!hasConflicts(board, conflicts, N))
        {
            printBoard(board, N);
            return;
        }
        col = getColumnWithMaxConflicts(board, conflicts, N, col);

        oldRow = board[col];
        newRow = getRowWithMinConflicts(col, conflicts, N, oldRow);

        decreaseConflicts(conflicts, N, oldRow, col);
        board[col] = newRow;
        increaseConflicts(conflicts, N, newRow, col);

        i++;
    }
}

int main()
{
    srand (time(NULL));
    int N;
    cout<<"Enter N: ";
    cin>>N;

    nQueens(N);
}
