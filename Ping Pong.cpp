#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;

// Ping Pong Game
bool gameOver;
string winner;
int score1, score2;
int length = 20;
int width = 60;
int px; //x axis(length) of both p1 & p2
int p1y, p2y; //y axis(width)
vector<int>p1;
vector<int>p2;
              //left  right upleft upright downleft downright
vector<char>dir{ 'a' , 'd' , 'q' ,   'e' ,   'z' ,    'c' };
char ballDirection;
bool start = false; // We created this so that after the game resets, the ball moves only after one of the players moves first

class Ball
{
public:
    int x, y;

    Ball(){}

    void reset()
    {
        x = length/2;
        y = width/2;
    }

    void moveBall(char direction)
    {
        switch(direction)
        {
            case 'a':
            --y;
            break;

            case 'd':
            ++y;
            break;

            case 'q':
            --x; --y;
            break;

            case 'e':
            --x; ++y;
            break;

            case 'z':
            ++x; --y;
            break;

            case 'c':
            ++x; ++y;
            break;

            default:
            break;
    }
   }
};

void Setup()
{
    gameOver = false;
    px = length/2;
    p1y = 2;
    p2y = width-1;
    score1 = 0;
    score2 = 0;

    p1 = {px-2, px-1, px, px+1, px+2};
    p2 = p1;
}

Ball b{};
void Draw()
{
    system("cls");
    cout<<setw(35)<<"Ping Pong"<<endl<<endl;;

    for(int i=1; i<=width; ++i)
    cout<<"#";

    cout<<endl;
    for(int i=1; i<=length; ++i)
    {
        for(int j=1; j<=width; ++j)
        {
            if(i == b.x && j == b.y)
                cout<<"O";
            else if(j == 1)
                cout<<"#";
            else if(j == width)
                cout<<"#"<<endl;
            else
            {
                if(j == p1y)
                {
                    if(i == p1[0] || i == p1[1] || i == p1[2] || i == p1[3] || i == p1[4])
                    cout<<"|";
                    else
                    cout<<" ";
                }
                else if(j == p2y)
                {
                    if(i == p2[0] || i == p2[1] || i == p2[2] || i == p2[3] || i == p2[4])
                    cout<<"|";
                    else
                    cout<<" ";
                }
                else
                cout<<" ";
            }
        }
    }

    for(int i=1; i<=width; ++i)
    cout<<"#";

    cout<<endl;

    cout<<"Player1:"<<score1<<setw(width-9)<<"Player2:"<<score2;
}

void startGame()
{
    ballDirection = dir[rand()%dir.size()];
}

void Action()
{
    if(_kbhit())
    {
        if(start == false)
        {
            start = true;
            startGame();
        }

        switch(_getch())
        {
            case 'w':
            {
                if(p1[0] != 1)
                {
                    for(auto &x: p1)--x;
                }

                break;
            }
            case 's':
            {
                if(p1[p1.size()-1] != length)
                {
                   for(auto &x: p1)++x;
                }

                break;
            }
            case 'i':
            {
                if(p2[0] != 1)
                {
                   for(auto &x: p2)--x;
                }
                break;
            }
            case 'k':
            {
                if(p2[p2.size()-1] != length)
                {
                    for(auto &x: p2)++x;
                }

                break;
            }
            default:
            break;
        }
    }
}

void moves()
{
    b.moveBall(ballDirection);
}

void checkBall()
{
    if(b.y == 1)
    {
        ++score2;
        ballDirection = ' ';
        start = false;
        b.reset();
    }
    else if(b.y == width)
    {
        ++score1;
        ballDirection = ' ';
        start = false;
        b.reset();
    }
    else if(b.x < 1)
    {
        if(ballDirection == 'q')
        ballDirection = 'z';
        else if(ballDirection == 'e')
        ballDirection = 'c';
    }
    else if(b.x > length)
    {
        if(ballDirection == 'c')
        ballDirection = 'e';
        else if(ballDirection == 'z')
        ballDirection = 'q';
    }
    else if(b.y == 2)
    {
        if(b.x == p1[0])
        ballDirection = 'e';
        else if(b.x == p1[1] || b.x == p1[2] || b.x == p1[3])
        ballDirection = 'd';
        else if(b.x == p1[4])
        ballDirection = 'c';
    }
    else if(b.y == width-1)
    {
        if(b.x == p2[0])
        ballDirection = 'q';
        else if(b.x == p2[1] || b.x == p2[2] || b.x == p2[3])
        ballDirection = 'a';
        else if(b.x == p2[4])
        ballDirection = 'z';
    }
}

void checkWin()
{
    if(score1 == 5)
    {
        winner = "Player1 wins";
        gameOver = true;
    }

    if(score2 == 5)
    {
        winner = "Player2 wins";
        gameOver = true;
    }
}
int main()
{
    Setup();
    b.reset();

    do{
    Draw();

    moves();

    Action();

    checkBall();

    checkWin();

    Sleep(10);
    }while(gameOver == false);

    cout<<"\n\n"<<winner;
    return 0;
}
