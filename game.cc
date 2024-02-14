#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showboard(char board[][SIDE])
{
    cout<<"\t\t\t "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<"\n";
    cout<<"\t\t\t---------------------\n";
    cout<<"\t\t\t "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<"\n";
    cout<<"\t\t\t---------------------\n";
    cout<<"\t\t\t "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<"\n";
}

void instructions()
{
    cout<<endl<<"Choose a cell numbered from 1 to 9 as below and play \n\n";

    cout<<"\t\t\t 1 | 2 | 3\n";
    cout<<"\t\t\t-----------\n";
    cout<<"\t\t\t 4 | 5 | 6\n";
    cout<<"\t\t\t-----------\n";
    cout<<"\t\t\t 7 | 8 | 9\n";
    cout<<"\t\t\t------------\n";
}

void initialize(char board[][SIDE])
{
    for(int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
        {
            board[i][j]='*';
        }
    }
}

void declarewinner(int whoseturn)
{
    if(whoseturn==COMPUTER)
    cout<<"COMPUTER has won\n";

    else
    cout<<"HUMAN has won\n";
}

bool rowcrossed(char board[][SIDE])
{
    for(int i=0;i<SIDE;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='*')
        return true;
    }
    return false;
}

bool columncrossed(char board[][SIDE])
{
    for(int i=0;i<SIDE;i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*')
        return true;
    }
    return false;
}

bool diagonalcrossed(char board[][SIDE])
{
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='*')
    return true;

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='*')
    return true;

    return false;
}

bool gameover(char board[][SIDE])
{
    return (rowcrossed(board) || columncrossed(board) || diagonalcrossed(board));
}

int minimax(char board[][SIDE],int depth,bool isAI)
{
    int score=0,bestscore=0;

    if(gameover(board)==true)
    {
        if(isAI==true)
        return -10;

        if(isAI==false)
        return 10;
    }

    else
    {
        if(depth<9)
        {
            if(isAI==true)
            {
                bestscore=-999;
                for(int i=0;i<SIDE;i++)
                {
                    for(int j=0;j<SIDE;j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=COMPUTERMOVE;
                            score=minimax(board,depth+1,false);
                            board[i][j]='*';
                            if(score>bestscore)
                            {
                                bestscore=score;
                            }
                        }
                    }
                }
                return bestscore;
            }

            else
            {
                bestscore=999;
                for(int i=0;i<SIDE;i++)
                {
                    for(int j=0;j<SIDE;j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=HUMANMOVE;
                            score=minimax(board,depth+1,false);
                            board[i][j]='*';
                            if(score<bestscore)
                            {
                                bestscore=score;
                            }
                        }
                    }
                }
                return bestscore;
            }
        }

        else
        {
            return 0;
        }
    }
}

int bestmove(char board[][SIDE],int moveindex)
{
    int x=-1,y=-1;
    int score=0,bestscore=-999;
                for(int i=0;i<SIDE;i++)
                {
                    for(int j=0;j<SIDE;j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=COMPUTERMOVE;
                            score=minimax(board,moveindex+1,false);
                            board[i][j]='*';
                            if(score>bestscore)
                            {
                                bestscore=score;
                                x=i;
                                y=j;
                            }
                        }
                    }
                }
return 3*x + y;
}

void tictactoe(int whoseturn)
{
    char board[SIDE][SIDE];
    int moveindex=0,x=0,y=0;

    initialize(board);
    instructions();

    while(gameover(board)==false && moveindex!=SIDE*SIDE)
    {
        int n;
        if(whoseturn==COMPUTER)
        {
            n=bestmove(board,moveindex);
            x=n/SIDE;
            y=n%SIDE;
            board[x][y]=COMPUTERMOVE;
            cout<<"COMPUTER has put "<<COMPUTERMOVE<<" in cell "<<n+1<<"\n";
            showboard(board);
            moveindex++;
            whoseturn=HUMAN;
        }

        else if(whoseturn==HUMAN)
        {
            cout<<"You can insert at the following positions : ";
            for(int i=0;i<SIDE;i++)
            {
                for(int j=0;j<SIDE;j++)
                {
                    if(board[i][j]=='*')
                    {
                        cout<<((3*i+j)+1)<<" ";
                    }
                }
            }

            cout<<"\n\n Enter the position : ";
            cin>>n;
            n--;
            x=n/SIDE;
            y=n%SIDE;
            if(board[x][y]=='*' && n<9 && n>=0)
            {
                board[x][y]=HUMANMOVE;
                cout<<"HUMAN has put "<<HUMANMOVE<<" in cell "<<n+1<<"\n";
                showboard(board);
                moveindex++;
                whoseturn=COMPUTER;
            }

            else if(board[x][y]!='*' && n<9 && n>=0)
            {
                cout<<"\nPosition is occupied, please select another position\n";
            }

            else if(n<0 || n>8)
            {
                cout<<"Invalid position\n";
            }
        }
    }

    if(gameover(board)==false && moveindex==SIDE*SIDE)
    cout<<"It is a draw\n";

    else
    {
        if(whoseturn==COMPUTER)
        whoseturn=HUMAN;

        else if(whoseturn==HUMAN)
        whoseturn=COMPUTER;

        declarewinner(whoseturn);
    }
}

int main()
{
    cout<<"\n--------------------------------------------------------\n\n";
    cout<<"\t\t\t Tic-Tac-Toe\n";
    cout<<"\n---------------------------------------------------------\n\n";
    char cont='y';
    do{
        char choice;
        cout<<"Do you want to start first? (y/n) : ";
        cin>>choice;

        if(choice=='n')
        tictactoe(COMPUTER);

        else if(choice=='y')
        tictactoe(HUMAN);

        else
        cout<<"Invalid choice\n";

        cout<<"\nDo yu want to quit(y/n) : ";
        cin>>cont;
    }while(cont=='n');
    return 0;    
}