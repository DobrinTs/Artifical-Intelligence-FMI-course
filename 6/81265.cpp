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

int maxValue(const vector<char>& board, int alpha, int beta, int depth, bool playerFirst);
int minValue(const vector<char>& board, int alpha, int beta, int depth, bool playerFirst);

int maxValue(const vector<char>& board, int alpha, int beta, int depth, bool playerFirst)
{
    char isTerminalResult = isTerminal(board);
    if(playerFirst && isTerminalResult  == 'O' ||
        !playerFirst && isTerminalResult=='X')
    {
        return 10-depth;
    }
    else if(playerFirst && isTerminalResult  == 'X' ||
            !playerFirst && isTerminalResult == 'O')
    {
        return depth - 10;
    }
    else if(isTerminalResult  == 'D')
    {
        return 0;
    }

    int v = MIN_INF;
    vector<char> newBoard;
    for(int i=0; i<9; i++)
    {
        if(board[i] == ' ')
        {
            newBoard=board;
            newBoard[i] = playerFirst? 'O' : 'X';
            v=max(v, minValue(newBoard, alpha, beta, depth+1, playerFirst));
            if(v >= beta) return v;
            alpha = max(alpha, v);
        }
    }
    return v;
}

int minValue(const vector<char>& board, int alpha, int beta, int depth, bool playerFirst)
{
    char isTerminalResult = isTerminal(board);

    if(playerFirst && isTerminalResult  == 'O' ||
        !playerFirst && isTerminalResult=='X')
    {
        return 10-depth;
    }
    else if(playerFirst && isTerminalResult  == 'X' ||
            !playerFirst && isTerminalResult == 'O')
    {
        return depth - 10;
    }
    else if(isTerminalResult  == 'D')
    {
        return 0;
    }

    int v = PLUS_INF;
    vector<char> newBoard;
    for(int i=0; i<9; i++)
    {
        if(board[i] == ' ')
        {
            newBoard=board;
            newBoard[i] = playerFirst? 'X' : 'O';
            v=min(v, maxValue(newBoard, alpha, beta, depth+1, playerFirst));
            if(v <= alpha) return v;
            beta = min (beta, v);
        }
    }
    return v;
}

int minMaxDecision(const vector<char>& board, bool playerFirst)
{
    int v = MIN_INF;
    vector<char> newBoard;
    int toPlayIdx;

    int alpha = MIN_INF;
    int beta = PLUS_INF;

    for(int i=0; i<9; i++)
    {
        if(board[i] == ' ')
        {
            newBoard=board;
            newBoard[i] = playerFirst ? 'O' : 'X';
            int minResult = minValue(newBoard, alpha, beta, 1, playerFirst);
            if(minResult > v)
            {
                v=minResult;
                toPlayIdx = i;
            }
            if(v >= beta) break;
            alpha = max(alpha, v);
        }
    }
    return toPlayIdx;
}

void tictactoe()
{
    vector<char> board(9, ' ');
    char t;
    cout<<"Who goes first? (0 for ai, 1 for player): ";
    bool playerFirst;
    cin>>playerFirst;

    int cell; // between 0 and 8
    int row, col;

    if(playerFirst) {
        printBoard(board);
        cout<<endl;
        cout<<endl<<"Enter cell coordinates: ";
        cin>>row>>col;
        cell = 3*(row -1) + (col - 1);

        while(cell<0 || cell>8 || board[cell]!=' ')
        {
            cout<<"Incorrect cell! Please enter a new one: ";
            cin>>row>>col;
            cell = 3*(row -1) + (col - 1);
        }
        board[cell] = 'X';
    }



    while((t = isTerminal(board)) == 'N')
    {
        board[minMaxDecision(board, playerFirst)] = playerFirst ? 'O' : 'X';
        printBoard(board);
        cout<<endl;

        t = isTerminal(board);
        if(t != 'N') {
           break;
        }

        cout<<endl<<"Enter cell coordinates: ";
        cin>>row>>col;
        cell = 3*(row -1) + (col - 1);

        while(cell<0 || cell>8 || board[cell]!=' ')
        {
            cout<<"Incorrect cell! Please enter a new one: ";
            cin>>row>>col;
            cell = 3*(row -1) + (col - 1);
        }
        board[cell] = playerFirst? 'X' : 'O';
        cout<<endl;
    }

    if(t == TERMINAL_DRAW)
    {
        cout<<"It's a draw!!";
    }
    else if(t == TERMINAL_X_WIN && !playerFirst
            || t==TERMINAL_O_WIN && playerFirst)
    {
        cout<<"Computer won game!";
    }
    else if(t == TERMINAL_O_WIN && !playerFirst
            || t==TERMINAL_X_WIN && playerFirst)
    {
        cout<<"Player won!";
    }
}

int main()
{
    tictactoe();
}
