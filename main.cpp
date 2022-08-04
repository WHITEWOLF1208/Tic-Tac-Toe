// Tic Tac Toe
#include<bits/stdc++.h>
using namespace std;
#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define CM 'O'
#define HM 'X'

void showBoard(char board[][SIDE])
{
    cout<<"    "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
    cout<<"   -----------"<<endl;
    cout<<"    "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
    cout<<"   -----------"<<endl;
    cout<<"    "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl;
}

void showInstructions()
{
    cout<<" Choose a cell numbered from 1 to 9 as below and play"<<endl;
    cout<<endl;
    cout<<"    1 | 2 | 3 "<<endl;
    cout<<"   -----------"<<endl;
    cout<<"    4 | 5 | 6 "<<endl;
    cout<<"   -----------"<<endl;
    cout<<"    7 | 8 | 9 "<<endl;
    cout<<endl;
}

void initialise(char board[][SIDE])
{
    // Initially the board to '*' as said
    for (int i=0; i<SIDE; i++)
    {
        for (int j=0; j<SIDE; j++)
        {
            board[i][j] = '*';
        }
        
    }
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER)
    {
        cout<<"COMPUTER has WON"<<endl;
    }
    else
    {
        cout<<"HUMAN has WON"<<endl;
    }
}

bool rowCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
        {
            return true;
        }
    }
    return false;
}

bool columnCrossed(char board[][SIDE])
{
    for (int i=0; i<SIDE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
        {
            return true;
        }
    }
    return(false);
}

bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
    {
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
    {
        return true;
    }
    return false;
}

bool gameOver(char board[][SIDE])
{
    return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
        {
            return -10;
        }
        
        if (isAI == false)
        {
            return +10;
        }
        
    }
    else
    {
        if(depth < 9)
        {
            if(isAI == true)
            {
                bestScore = -999;
                for(int i=0; i<SIDE; i++)
                {
                    for(int j=0; j<SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = CM;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if(score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                        {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = HM;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
}

int bestMove(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = CM;
                score = minimax(board, moveIndex+1, false);
                board[i][j] = '*';
                if(score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x*3+y;
}

void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;
    initialise(board);
    showInstructions();
    while (gameOver(board) == false && moveIndex != SIDE*SIDE)
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] =CM;
            cout<<"COMPUTER has put a "<<CM<<" in cell "<<n+1<<endl;
            showBoard(board);
            moveIndex ++;
            whoseTurn = HUMAN;
        }
        else if (whoseTurn == HUMAN)
        {
            cout<<"You can insert in the following positions : "<<endl;
            for(int i=0; i<SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == '*')
                    {
                        cout<<((i * 3 + j) + 1)<<endl;
                    }
                }
            }
            cout<<"Enter the position = "<<endl;
            cin>>n;
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if(board[x][y] == '*' && n<9 && n>=0)
            {
                board[x][y] = HM;
                cout<<"HUMAN has put a "<<HM<<" in cell "<<n+1<<endl;
                showBoard(board);
                moveIndex ++;
                whoseTurn = COMPUTER;
            }
            else if(board[x][y] != '*' && n<9 && n>=0)
            {
                cout<<"Position is occupied, select any one place from the available places"<<endl;
            }
            else if(n<0 || n>8)
            {
                cout<<"Invalid position"<<endl;
            }
        }
    }
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
    {
        cout<<"It's a draw"<<endl;
    }
    else
    {
        if (whoseTurn == COMPUTER)
        {
            whoseTurn = HUMAN;
        }
        else if (whoseTurn == HUMAN)
        {
            whoseTurn = COMPUTER;
        }
        declareWinner(whoseTurn);
    }
}

int main()
{
    cout<<"-------------------------------------------------------------------"<<endl;
    cout<<"                          "<<"Tic-Tac-Toe"<<endl;
    cout<<"-------------------------------------------------------------------"<<endl;
    char cont='y';
    do
    {
        char choice;
        cout<<"Do you want to start first?(y/n) : "<<endl;
        cin>>choice;
        if(choice=='n')
        {
            //playTicTacToe(COMPUTER);
            cout<<"N"<<endl;
        }
        else if(choice=='y')
        {
            //playTicTacToe(HUMAN);
            cout<<"Y"<<endl;
        }
        else
        {
            cout<<"Invalid choice"<<endl;
        }
        
        cout<<"Do you want to quit(y/n) : "<<endl;
        cin>>cont;
    } 
    while(cont=='n');
    return (0);
}