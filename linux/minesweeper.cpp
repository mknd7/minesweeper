/**
    Minesweeper Game (clone)
    Console version
    Minesweeper.cpp

    @author Mukund Vijayaraghavan
    @version 1.0, Nov 2015
*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include "getch.h"

using namespace std;

struct Square
{
    bool exp;                           // exposed or not
    int val;                            // value of square (-1 for mine)
};

class Field
{
    Square s[16][16];                           // game field
    int n,m,mines;                              // rows, columns and mines
    char diff;                                  // difficulty
    bool game_run;                              // game state
    bool game_win;                              // win or lose

    /**
        Function which set difficulty
        Initializes field dimensions and number of mines
    */
    void diff_in()
    {
        cout<<"\nEnter difficulty (normal or hard) (n/h): ";
        /*
            Normal is 9*9 with 10 mines
            Hard is 16*16 with 40 mines
        */
        while(1)
        {
            cin>>diff;
            if(diff=='n'||diff=='N')
            {
                n = m = 9;
                mines = 10;
                break;
            }
            else if(diff=='h'||diff=='H')
            {
                n = m = 16;
                mines = 40;
                break;
            }
            else
                cout<<"\nInvalid! Enter again.\n";
        }
    }

    /**
        Helper function which places mines in the field
    */
    void init()
    {
        int x,y;
        int i = mines;
        srand(time(NULL));                              // intializing random number generator
        while(i--)
        {
            x = rand()%n;                               // random row
            y = rand()%m;                               // random column
            if(s[x][y].val==-1)
                i++;
            else
                s[x][y].val=-1;
        }
    }

    /**
        Function for first player move
        If first encountered square is a mine,
        move_mine() is used.
    */
    void first_move()
    {
        int x,y;
        cout<<"\n\tEnter row\n\t";
        cin>>x;
        cout<<"\tEnter column\n\t";
        cin>>y;
        --x;
        --y;
        if(s[x][y].val==-1)
            move_mine(x,y);
        fill_values();
        if(s[x][y].val!=0)
            s[x][y].exp = true;
        else
            reveal(x,y);
    }

    /**
        Helper function to move mine
        to a new random location

        @param co-ordinates of mine location
    */
    void move_mine(int x,int y)
    {
        s[x][y].val = 0;
        srand(time(NULL));
        while(1)
        {
            x = rand()%n;
            y = rand()%m;
            if(s[x][y].val!=-1)
            {
                s[x][y].val=-1;
                break;
            }
        }
    }

    /**
        Helper function to fill values of the field
    */
    void fill_values()
    {
        int value,i,j;
        for(j=0;j<m;j++)                        // for first row
        {
            value = 0;
            if(s[0][j].val==-1)
                continue;
            else
            {
                if(j==0)                        // for first column
                {
                    if(s[0][1].val==-1)
                        value++;
                    if(s[1][0].val==-1)
                        value++;
                    if(s[1][1].val==-1)
                        value++;
                    s[0][0].val = value;
                }
                else if(j==m-1)                 // for last column
                {
                    if(s[0][m-2].val==-1)
                        value++;
                    if(s[1][m-1].val==-1)
                        value++;
                    if(s[1][m-2].val==-1)
                        value++;
                    s[0][m-1].val = value;
                }
                else                            // for middle columns
                {
                    if(s[0][j-1].val==-1)
                        value++;
                    if(s[0][j+1].val==-1)
                        value++;
                    if(s[1][j-1].val==-1)
                        value++;
                    if(s[1][j].val==-1)
                        value++;
                    if(s[1][j+1].val==-1)
                        value++;
                    s[0][j].val = value;
                }
            }
        }
        for(j=0;j<m;j++)                        // for last row
        {
            value = 0;
            if(s[n-1][j].val==-1)
                continue;
            else
            {
                if(j==0)                        // for first column
                {
                    if(s[n-2][0].val==-1)
                        value++;
                    if(s[n-2][1].val==-1)
                        value++;
                    if(s[n-1][2].val==-1)
                        value++;
                    s[n-1][0].val = value;
                }
                else if(j==m-1)                 // for last column
                {
                    if(s[n-2][m-1].val==-1)
                        value++;
                    if(s[n-2][m-2].val==-1)
                        value++;
                    if(s[n-1][m-2].val==-1)
                        value++;
                    s[n-1][m-1].val = value;
                }
                else                            // for middle columns
                {
                    if(s[n-1][j-1].val==-1)
                        value++;
                    if(s[n-2][j-1].val==-1)
                        value++;
                    if(s[n-2][j].val==-1)
                        value++;
                    if(s[n-2][j+1].val==-1)
                        value++;
                    if(s[n-1][j+1].val==-1)
                        value++;
                    s[n-1][j].val = value;
                }
            }
        }
        for(i=1;i<n-1;i++)                      // for first column (middle rows)
        {
            value = 0;
            if(s[i][0].val==-1)
                continue;
            else
            {
                if(s[i-1][0].val==-1)
                    value++;
                if(s[i-1][1].val==-1)
                    value++;
                if(s[i][1].val==-1)
                    value++;
                if(s[i+1][0].val==-1)
                    value++;
                if(s[i+1][1].val==-1)
                    value++;
                s[i][0].val = value;
            }
        }
        for(i=1;i<n-1;i++)                      // for last column (middle rows)
        {
            value = 0;
            if(s[i][m-1].val==-1)
                continue;
            else
            {
                if(s[i-1][m-1].val==-1)
                    value++;
                if(s[i-1][m-2].val==-1)
                    value++;
                if(s[i][m-2].val==-1)
                    value++;
                if(s[i+1][m-2].val==-1)
                    value++;
                if(s[i+1][m-1].val==-1)
                    value++;
                s[i][m-1].val = value;
            }
        }
        for(i=1;i<n-1;i++)                      // all middle values
        {
            for(j=1;j<m-1;j++)
            {
                value = 0;
                if(s[i][j].val==-1)
                    continue;
                else
                {
                    if(s[i-1][j-1].val==-1)
                        value++;
                    if(s[i-1][j].val==-1)
                        value++;
                    if(s[i-1][j+1].val==-1)
                        value++;
                    if(s[i][j-1].val==-1)
                        value++;
                    if(s[i][j+1].val==-1)
                        value++;
                    if(s[i+1][j-1].val==-1)
                        value++;
                    if(s[i+1][j].val==-1)
                        value++;
                    if(s[i+1][j+1].val==-1)
                        value++;
                    s[i][j].val = value;
                }
            }
        }
    }

    /**
        Function (recursive) which
        reveals surrounding squares

        @param co-ordinates of selected square
    */
    void reveal(int x,int y)
    {
        if(s[x][y].val==0)
        {
            if(s[x][y].exp == true)
                return;
            else
                s[x][y].exp = true;
            if(x==0)                                // for first row
            {
                if(y==0)                            // for first column
                {
                    reveal(x,y+1);
                    reveal(x+1,y);
                    reveal(x+1,y+1);
                }
                else if(y==m-1)                     // for last column
                {
                    reveal(x,y-1);
                    reveal(x+1,y-1);
                    reveal(x+1,y);
                }
                else                                // for middle columns
                {
                    reveal(x,y-1);
                    reveal(x,y+1);
                    reveal(x+1,y-1);
                    reveal(x+1,y);
                    reveal(x+1,y+1);
                }
            }
            else if(x==n-1)                         // for last row
            {
                if(y==0)                            // for first column
                {
                    reveal(x-1,y);
                    reveal(x-1,y+1);
                    reveal(x,y+1);
                }
                else if(y==m-1)                     // for last column
                {
                    reveal(x-1,y-1);
                    reveal(x-1,y);
                    reveal(x,y-1);
                }
                else                                // for middle columns
                {
                    reveal(x,y-1);
                    reveal(x-1,y-1);
                    reveal(x-1,y);
                    reveal(x-1,y+1);
                    reveal(x,y+1);
                }
            }
            else                                    // for middle rows
            {
                if(y==0)                            // for first column
                {
                    reveal(x-1,y);
                    reveal(x-1,y+1);
                    reveal(x,y+1);
                    reveal(x+1,y);
                    reveal(x+1,y+1);
                }
                else if(y==m-1)                     // for last column
                {
                    reveal(x-1,y);
                    reveal(x-1,y-1);
                    reveal(x,y-1);
                    reveal(x+1,y-1);
                    reveal(x+1,y);
                }
                else                                // for middle columns
                {
                    reveal(x-1,y-1);
                    reveal(x-1,y);
                    reveal(x-1,y+1);
                    reveal(x,y-1);
                    reveal(x,y+1);
                    reveal(x+1,y-1);
                    reveal(x+1,y);
                    reveal(x+1,y+1);
                }
            }
        }
        else
            if(s[x][y].val!=-1)
                s[x][y].exp = true;
    }

    /**
        Helper function to reveal all
        mines once game is over
    */
    void reveal_mines()
    {
        int i,j;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                if(s[i][j].val==-1)
                    s[i][j].exp = true;
    }

    /**
        Function to display field
        before every move
    */
    void disp()
    {
        system("clear");
        cout<<"\n\tMinesweeper\n\n";
        int i,j;
        cout<<"      ";
        for(j=0;j<m;j++)
        {
            cout<<j+1<<' ';
            if(j<8)
                cout<<' ';
        }
        cout<<"\n      ";
        for(j=0;j<m;j++)
                cout<<'^'<<"  ";
        cout<<'\n';
        for(i=0;i<n;i++)
        {
            cout<<i+1<<' ';
            if(i<9)
                cout<<" < ";
            else
                cout<<"< ";

            for(j=0;j<m;j++)
                if(s[i][j].exp == false)
                    cout<<" _ ";
                else
                    if(s[i][j].val==-1)
                        cout<<" * ";
                    else
                        cout<<' '<<s[i][j].val<<' ';
            cout<<'\n';
        }
    }

    /**
        Function for move made by player
    */
    void move()
    {
        int x,y;
        cout<<"\n\tEnter row\n\t";
        cin>>x;
        cout<<"\tEnter column\n\t";
        cin>>y;
        --x;
        --y;
        if(s[x][y].exp == true)
            return;
        if(s[x][y].val==-1)
        {
            game_run = false;
            game_win = false;
        }
        else
        {
            if(s[x][y].val!=0)
                s[x][y].exp = true;
            else
                reveal(x,y);
        }

        int count = 0;
        for(x=0;x<n;x++)
            for(y=0;y<m;y++)
                if(s[x][y].exp == false)
                    count++;
        if(count==mines)
        {
            game_run = false;
            game_win = true;
        }
    }

    public:

        Field()
        {
            game_run = true;
            game_win = false;
            for(int i=0;i<16;i++)
                for(int j=0;j<16;j++)
                {
                    s[i][j].exp = false;                        // unexposed (invisible)
                    s[i][j].val = 0;                            // default value (before fill)
                }
        }

        /**
            Main game function
        */
        void game()
        {
            diff_in();
            init();
            disp();
            first_move();
            // Main game loop
            while(game_run)
            {
                disp();
                move();
            }
            reveal_mines();
            disp();
            if(game_win == true)
                cout<<"\n\tYou won the game! :)\n\n";
            else
                cout<<"\n\tYou encountered a mine!\n\t\tGame Over :(\n\n";
        }
};

/**
    Function which starts a new
    instance of the game
*/
void start()
{
    system("clear");
    Field f;
    f.game();
    char op;
    cout<<"Would you like to play another game? (y/n): ";
    cin>>op;
    if(op=='y'||op=='Y')
        start();
    else
        exit(0);
}

int main()
{
    system("clear");
    cout<<"Welcome to the text-based version of minesweeper\n";
    cout<<"\nMinesweeper is a single-player puzzle game.\n"
            "The player is presented with a grid of identical "
            "objects (squares most often),\nsome of which have "
            "mines hidden underneath.\n";
    cout<<"\n\t*If the player encounters a mine, he/she loses.\n";
    cout<<"\t*A square with its number revealed indicates the "
            "number of mines\n\tsurrounding that square"
            "(adjacent and diagonal).\n";
    cout<<"\t*An empty square (denoted by 0) indicates that it is "
             "not in the vicnity\n\tof any of the mines and will "
             "reveal surrounding squares\n";
    cout<<"\t*The game is won by reavealing all the squares without "
             "encountering a\n\tmine.\n\n";
    cout<<"\nIn this version of the game,\nThe player must type their input.\n";
    cout<<"\nThere are 2 difficulties:\nNormal:  9 * 9 field with 10 mines\n"
            "Hard: 16 * 16 field with 40 mines\n";
    cout<<"\nPress Enter to continue.";
    char c;
    while((c = getch())!=10) // ASCII value for Enter
    {}
    //Different method
    //while((c = cin.get())!='\n')
    //{}
    start();
    return 0;
}