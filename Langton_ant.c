#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/ioctl.h> //Terminal Size Library

#define for_x for(int x = 0; x < Term_Length; ++x)
#define for_y for(int y = 0; y < Term_Height; ++y)
#define cycle for_y for_x

#define current_square grid[y % Term_Height][x % Term_Length] //[y % Term_Height][x % Term_Length]
#define ant_square grid[ant_y % Term_Height][ant_x % Term_Length]

unsigned long long int generation;

int Term_Height;
int Term_Length;

int ant_x, ant_y;

int angle_counter = 1;
char angles[4] = {'U', 'R', 'D', 'L'};

int Skip_rate = 0;

int main(void)
{

    void fSetStage(bool grid[][Term_Length]);
    void fPrintGrid(bool grid[][Term_Length]);
    void fFind(bool grid[][Term_Length]);


    //Getting The Size of the Terminal 
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    Term_Height = -1 + (int) w.ws_row;
    Term_Length = (int) w.ws_col;
    
    //printf ("Up-Down %i\n", Term_Height);
    //printf ("Left-Right %i\n", Term_Length);

    bool grid[Term_Height][Term_Length];

    fSetStage(grid);

    printf("Skip Rate - ");
    scanf("%i", &Skip_rate);

    for(generation = 0; generation < ULONG_MAX; ++generation)
    {   
        fFind(grid);
        if(generation % Skip_rate == 0)
        {
            fPrintGrid(grid);
            usleep(100000);
            system("Clear");
        }
    }
}

void fFind(bool grid[][Term_Length])
{
    if(!ant_square) //It's White
    {
        ++angle_counter;    
        if(angles[angle_counter % 4] == 'U')
        {
            ant_square = !ant_square;
            ++ant_y;
        }
        else if(angles[angle_counter % 4] == 'R')
        {
            ant_square = !ant_square;
            ++ant_x;
        }
        else if(angles[angle_counter % 4] == 'D')
        {
            ant_square = !ant_square;
            --ant_y;
        }
        else if(angles[angle_counter % 4] == 'L')
        {
            ant_square = !ant_square;
            --ant_x;
        }    
    }

    else if(ant_square) //It's Black
    {
        --angle_counter;
        if(angles[angle_counter % 4] == 'U')
        {
            ant_square = !ant_square;
            ++ant_y;
        }
        else if(angles[angle_counter % 4] == 'R')
        {
            ant_square = !ant_square;
            ++ant_x;
        }
        else if(angles[angle_counter % 4] == 'D')
        {
            ant_square = !ant_square;
            --ant_y;
        }
        else if(angles[angle_counter % 4] == 'L')
        {
            ant_square = !ant_square;
            --ant_x;
        }
    }
    if(ant_x < 0)
    {
            ant_x = Term_Length;
    }
    if(ant_y < 0)
    {
            ant_y = Term_Height;
    }
}

void fSetStage(bool grid[][Term_Length])
{
    cycle
        current_square = false;

    ant_x = Term_Length / 2;
    ant_y = Term_Height / 2;
}

void fPrintGrid(bool grid[][Term_Length])
{
    printf("Generation - %llu  angle_counter - %i  ant_x - %i, ant_y - %i", generation, angle_counter, ant_x, ant_y); 
    for_y
    {
        printf("\n");
        for_x
        {
        if(x == ant_x && y == ant_y)
            printf("*");
        else if(current_square)
            printf("#");
        else    
            printf(" ");
        }
    }
}

