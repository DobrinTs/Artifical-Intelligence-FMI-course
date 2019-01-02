#include<iostream>
#include<math.h>
#include<queue>
#include <unordered_set>
using namespace std;

int manhattanDistance(int** board, int boardSize)
{
    int sum = 0;
    int shouldBeI, shouldBeJ;
    int cellValue;

    for(int i=0; i<boardSize; i++)
    {
        for(int j=0; j<boardSize; j++)
        {
            cellValue = board[i][j];
            if(board[i][j] == 0)
            {
                shouldBeI = shouldBeJ = boardSize - 1;
            }
            else
            {
                shouldBeI = (cellValue - 1) / boardSize;
                shouldBeJ = (cellValue - 1) % boardSize;
            }
            sum += abs(i - shouldBeI) + abs(j - shouldBeJ);
        }
    }
    return sum;
}

void printBoard(int** board, int boardSize)
{
    for(int i=0; i<boardSize; i++)
    {
        for(int j=0; j<boardSize; j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

int** copyBoard(int** board, int boardSize)
{
    int** newBoard = new int*[boardSize];
    for(int i=0; i<boardSize; i++)
    {
        newBoard[i] = new int[boardSize];
        for(int j=0; j<boardSize; j++)
        {
            newBoard[i][j] = board[i][j];
        }
    }

    return newBoard;
}

struct BoardStatus
{
    int** board;
    int boardSize;
    int distanceSoFar;
    string trace;
    int manhattanDist;
    int zeroRow;
    int zeroCol;

    bool canMoveLeft()
    {
        return zeroCol < boardSize - 1;
    }

    BoardStatus* moveLeft()
    {
        BoardStatus* result = new BoardStatus(*this);
        result->board[result->zeroRow][result->zeroCol] =
            result->board[result->zeroRow][result->zeroCol + 1];
        result->board[result->zeroRow][result->zeroCol + 1] = 0;
        result->zeroCol += 1;
        result->manhattanDist = manhattanDistance(result->board, result->boardSize);
        result->distanceSoFar += 1;
        result->trace = result->trace + "l";

        return result;
    }

    bool canMoveRight()
    {
        return zeroCol > 0;
    }

    BoardStatus* moveRight()
    {
        BoardStatus* result = new BoardStatus(*this);
        result->board[result->zeroRow][result->zeroCol] =
            result->board[result->zeroRow][result->zeroCol - 1];
        result->board[result->zeroRow][result->zeroCol - 1] = 0;
        result->zeroCol -= 1;
        result->manhattanDist = manhattanDistance(result->board, result->boardSize);
        result->distanceSoFar += 1;
        result->trace = result->trace + "r";

        return result;
    }

    bool canMoveUp()
    {
        return zeroRow < boardSize - 1;
    }

    BoardStatus* moveUp()
    {
        BoardStatus* result = new BoardStatus(*this);
        result->board[result->zeroRow][result->zeroCol] =
            result->board[result->zeroRow + 1][result->zeroCol];
        result->board[result->zeroRow + 1][result->zeroCol] = 0;
        result->zeroRow += 1;
        result->manhattanDist = manhattanDistance(result->board, result->boardSize);
        result->distanceSoFar += 1;
        result->trace = result->trace + "u";

        return result;
    }

    bool canMoveDown()
    {
        return zeroRow > 0;
    }

    BoardStatus* moveDown()
    {
        BoardStatus* result = new BoardStatus(*this);
        result->board[result->zeroRow][result->zeroCol] =
            result->board[result->zeroRow - 1][result->zeroCol];
        result->board[result->zeroRow - 1][result->zeroCol] = 0;
        result->zeroRow -= 1;
        result->manhattanDist = manhattanDistance(result->board, result->boardSize);
        result->distanceSoFar += 1;
        result->trace = result->trace + "d";

        return result;
    }

    BoardStatus(int** board, int boardSize, int distanceSoFar, string trace)
    {
        this->board = copyBoard(board, boardSize);
        this->boardSize = boardSize;
        this->distanceSoFar = distanceSoFar;
        this->trace = trace;
        this->manhattanDist = manhattanDistance(this->board, this->boardSize);

        for(int i=0; i<boardSize; i++)
        {
            for(int j=0; j<boardSize; j++)
            {
                if(board[i][j] == 0)
                {
                    this->zeroRow = i;
                    this->zeroCol = j;
                }
            }
        }
    }

    BoardStatus(const BoardStatus& other)
    {
        this->board = copyBoard(other.board, other.boardSize);
        this->boardSize = other.boardSize;
        this->distanceSoFar = other.distanceSoFar;
        this->trace = other.trace;
        this->manhattanDist = manhattanDistance(this->board, this->boardSize);
        this->zeroCol = other.zeroCol;
        this->zeroRow = other.zeroRow;
    }

    BoardStatus& operator=(const BoardStatus& other)
    {
        if(this != &other)
        {
            this->board = copyBoard(other.board, other.boardSize);
            this->boardSize = other.boardSize;
            this->distanceSoFar = other.distanceSoFar;
            this->trace = other.trace;
            this->manhattanDist = manhattanDistance(this->board, this->boardSize);
            this->zeroCol = other.zeroCol;
            this->zeroRow = other.zeroRow;
        }
        return *this;
    }

    ~BoardStatus()
    {
        for(int i=0; i<this->boardSize; i++)
        {
            delete[] board[i];
        }
        delete[] board;
    }

    bool operator ==(const BoardStatus &other) const
    {
        if(this->boardSize != other.boardSize)
        {
            return false;
        }
        for(int i=0; i< this->boardSize; i++)
        {
            for(int j=0; j< this->boardSize; j++)
            {
                if(this->board[i][j] != other.board[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator<(const BoardStatus &other) const
    {
        return this->distanceSoFar + this->manhattanDist > other.distanceSoFar + other.manhattanDist;
    }

    void print()
    {
        printBoard(this->board, this->boardSize);
        cout<<this->distanceSoFar<<" "<<this->manhattanDist<<" "<<this->trace<<endl;
        cout<<zeroRow<<" "<<zeroCol<<endl;
        cout<<"--------------------------------------"<<endl;
    }

    void printResult()
    {
        cout<<this->distanceSoFar<<endl;
        for(int i=0; i < this->trace.length(); i++)
        {
            if(this->trace[i] == 'u')
            {
                cout<<"up"<<endl;
            }
            else if(this->trace[i] == 'r')
            {
                cout<<"right"<<endl;
            }
            else if(this->trace[i] == 'd')
            {
                cout<<"down"<<endl;
            }
            else if(this->trace[i] == 'l')
            {
                cout<<"left"<<endl;
            }
        }
    }
};

struct BoardStatusHash
{
    std::size_t operator () ( const BoardStatus& b ) const
    {
        int hash = 0;
        for(int i=0; i < b.boardSize; i++)
        {
            for(int j=0; j < b.boardSize; j++)
            {
                hash += (i*b.boardSize + j) * b.board[i][j];
            }
        }
        return hash;
    }
};

void astar(int** board, int boardSize)
{
    BoardStatus start(board, boardSize, 0, "");

    unordered_set<BoardStatus, BoardStatusHash> visited;
    priority_queue<BoardStatus> pq;
    pq.push(start);

    BoardStatus top = pq.top();
    visited.insert(top);

    while(!pq.empty() && top.manhattanDist > 0)
    {
        pq.pop();
        if(top.canMoveUp())
        {
            BoardStatus* movedUp = top.moveUp();
            if(visited.count(*movedUp) == 0)
            {
                pq.push(*movedUp);
            }
        }
        if(top.canMoveRight())
        {
            BoardStatus* movedRight = top.moveRight();
            if(visited.count(*movedRight) == 0)
            {
                pq.push(*movedRight);
            }
        }
        if(top.canMoveDown())
        {
            BoardStatus* movedDown = top.moveDown();
            if(visited.count(*movedDown) == 0)
            {
                pq.push(*movedDown);
            }
        }
        if(top.canMoveLeft())
        {
            BoardStatus* movedLeft = top.moveLeft();
            if(visited.count(*movedLeft) == 0)
            {
                pq.push(*movedLeft);
            }
        }


        top = pq.top();
        visited.insert(top);
    }

    top.printResult();
}

int main()
{
    int N;
    cout<<"Enter number of enumerated tiles: ";
    cin>>N;
    int n = sqrt(N+1);

    cout<<"Enter game board: "<<endl;
    int** board = new int*[n];
    for(int i=0; i<n; i++)
    {
        board[i] = new int[n];
        for(int j=0; j<n; j++)
        {
            cin>>board[i][j];
        }
    }

    astar(board, n);
}
