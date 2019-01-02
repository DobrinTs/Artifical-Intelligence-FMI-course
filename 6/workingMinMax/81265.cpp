#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

const char TERMINAL_X_WIN = 'X';
const char TERMINAL_O_WIN = 'O';
const char TERMINAL_DRAW = 'D';
const char NOT_TERMINAL = 'N';

const int MIN_INF = -15;
const int PLUS_INF = 15;

void printBoard(const vector<char>& board)
{
    for(int i=0; i<9; i++)
    {
        if(i!=0 && i%3 == 0)
        {
            cout<<endl<<"-----------"<<endl;
        }
        cout<<board[i];
        if(i%3 != 2)
        {
            cout<<" | ";
        }
    }
}

char isTerminal(const vector<char>& board)   //returns X if X wins, O if O wins, D if draw, N if not terminal
{
    for(int i=0; i<3; i++)
    {
        int rowStart = i*3;
        if(board[rowStart] == board[rowStart+1] && board[rowStart] == board[rowStart+2])
        {
            if(board[rowStart] == 'X')
            {
                return TERMINAL_X_WIN;
            }
            else if(board[rowStart] == 'O')
            {
                return TERMINAL_O_WIN;
            }
        }

        int colStart = i;
        if(board[colStart] == board[colStart+3] && board[colStart] == board[colStart+6])
        {
            if(board[colStart] == 'X')
            {
                return TERMINAL_X_WIN;
            }
            else if(board[colStart] == 'O')
            {
                return TERMINAL_O_WIN;
            }
        }
    }

    if(board[0] == board[4] && board[0] == board[8])
    {
        if(board[0] == 'X')
        {
            return TERMINAL_X_WIN;
        }
        else if(board[0] == 'O')
        {
            return TERMINAL_O_WIN;
        }
    }

    if(board[6] == board[4] && board[6] == board[2])
    {
        if(board[6] == 'X')
        {
            return TERMINAL_X_WIN;
        }
        else if(board[6] == 'O')
        {
            return TERMINAL_O_WIN;
        }
    }

    bool isDraw = true;
    for(int i=0; i<9; i++)
    {
        if(board[i] == ' ')
        {
            isDraw = false;
        }
    }
    if(isDraw)
    {
        return TERMINAL_DRAW;
    }

    return NOT_TERMINAL;
}

int maxValue(const vector<char>& board, int depth,  int& traversalCount);
int minValue(const vector<char>& board, int depth,  int& traversalCount);

int maxValue(const vector<char>& board, int depth,  int& traversalCount)
{
    if(isTerminal(board) == 'X')
    {
        traversalCount++;
        return 10-depth;
    }
    else if(isTerminal(board) == 'O')
    {
        traversalCount++;
        return depth - 10;
    }
    else if(isTerminal(board) == 'D')
    {
        traversalCount++;
        return 0;
    }

    int v = MIN_INF;
    vector<char> newBoard;
    for(int i=0; i<9; i++)
    {
        if(board[i] == ' ')
        {
            newBoard=board;
            newBoard[i] = 'X';
            v=max(v, minValue(newBoard, depth+1, traversalCount));
        }
    }
    return v;
}

int minValue(const vector<char>& board, int depth, int& traversalCount)
{
    if(isTerminal(board) == 'X')
    {
        traversalCount++;

        return 10-depth;

    }
    else if(isTerminal(board) == 'O')
    {
        traversalCount++;

        return depth - 10;
    }
    else if(isTerminal(board) == 'D')
    {
        traversalCount++;

        return 0;
    }

    int v = PLUS_INF;
    vector<char> newBoard;
    for(int i=0; i<9; i++)
    {
        if(board[i] == ' ')
        {
            newBoard=board;
            newBoard[i] = 'O';
            v=min(v, maxValue(newBoard, depth+1, traversalCount));
        }
    }
    return v;
}

int minMaxDecision(const vector<char>& board)
{
    int v = MIN_INF;
    vector<char> newBoard;
    int toPlayIdx;

    int traversalCount = 0;

    for(int i=0; i<9; i++)
    {
        if(board[i] == ' ')
        {
            newBoard=board;
            newBoard[i] = 'X';
            int minResult = minValue(newBoard, 1, traversalCount);
            if(minResult > v)
            {
                v=minResult;
                toPlayIdx = i;
            }
        }
    }
    cout<<endl<<traversalCount<<endl;
    return toPlayIdx;
}

void tictactoe()
{
    vector<char> board(9, ' ');
    char t;

    board[minMaxDecision(board)] = 'X';
    printBoard(board);

    while((t = isTerminal(board)) == 'N')
    {
        int cell; // between 0 and 8
        int row, col;
        cout<<endl<<"Enter cell coordinates: ";
        cin>>row>>col;

        cell = 3*(row -1) + (col - 1);
        cout<<row<<" "<<col<<" "<<cell<<endl;

        while(cell<0 || cell>8 || board[cell]!=' ')
        {
            cout<<"Incorrect cell! Please enter a new one: ";
            cin>>row>>col;

        }
        board[cell] = 'O';

        board[minMaxDecision(board)] = 'X';
        printBoard(board);
        cout<<endl;
    }
    if(t == TERMINAL_DRAW)
    {
        cout<<"It's a draw!!";
    }
    else if(t == TERMINAL_X_WIN)
    {
        cout<<"Computer won game!";
    }
    else if(t == TERMINAL_O_WIN)
    {
        cout<<"Player won!";
    }
}

int main()
{
    tictactoe();
}
