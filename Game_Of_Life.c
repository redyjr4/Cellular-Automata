#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h> //Terminal Size Library

#define for_x for(int x = 0; x < iLength; ++x)
#define for_y for(int y = 0; y < iHeight; ++y)
#define cycle for_y for_x

#define current_cell argCells[y][x]
#define next_cell argFutureCells[y][x]

int generation;
int iHeight, iLength;

int main(void)
{   

    int Conway(int counter_alive, int y, int x, bool argCells[][iLength]); 

    void fSetStage(bool argCells[][iLength], bool argFutureCells[][iLength]);
    void fDraw(bool argCells[][iLength], bool argFutureCells[][iLength]);
    void fRefresh(bool argCells[][iLength], bool argFutureCells[][iLength]);
    void fFind(bool argCells[][iLength], bool argFutureCells[][iLength]);

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    //printf ("lines %d\n", w.ws_row);
    //printf ("columns %d\n", w.ws_col);

    iHeight = -2 + (int) w.ws_row;
    iLength = (int) w.ws_col;
    
    //printf ("lines %i\n", iHeight);
    //printf ("columns %i\n", iLength);

    bool cells[iHeight][iLength];
    bool future_cells[iHeight][iLength];

    fSetStage(cells, future_cells);
    fDraw(cells, future_cells);
    fRefresh(cells, future_cells);
    for(generation = 0; generation <= 1000; ++generation)
    {
        fFind(cells, future_cells);
        fRefresh(cells, future_cells);
        fDraw(cells, future_cells);
    }
}

int Conway(int counter_alive, int y, int x, bool argCells[][iLength])
{
    if(current_cell)
    {
        if(counter_alive == 2 || counter_alive == 3)
            return 1;
        else if(counter_alive < 2 || counter_alive > 3)
            return 0;
    }
    else
    {
        if(counter_alive == 3)
            return 1;
        else
            return 0;
    }
    return 0;
}

void fRefresh(bool argCells[][iLength], bool argFutureCells[][iLength])
{
    cycle
    {
        current_cell = next_cell;
    }
}

void fFind(bool argCells[][iLength], bool argFutureCells[][iLength])
{
    cycle
    {
        short int new_x, new_y;
        int counter_alive = 0;
        
        for(new_x = -1; new_x < 2; ++new_x)
        {
            for(new_y = -1; new_y < 2; ++new_y)
            {
                if(new_x == 0 && new_y == 0)
                    break;
        
                else if(x + new_x > iLength || x + new_x < 0 || y + new_y > iHeight || y + new_y < 0)
                    break;
    
                else if(argCells[y + new_y][x + new_x])
                    ++counter_alive;
            }
        }
        next_cell = Conway(counter_alive, y, x, argCells);
    }
}


void fDraw(bool argCells[][iLength], bool argFutureCells[][iLength])
{
    system("clear");
    printf("\n\n");
    printf("Generation - %i", generation);
    for_y
    {
        printf("\n");
        for_x
        {
            if(current_cell)
                printf("#");
            else
                printf(" ");
        }
    }
    usleep(60000);
    
}

void fSetStage(bool argCells[][iLength], bool argFutureCells[][iLength])
{
    srand(time(0));
    cycle
    {
        current_cell = 0;
        next_cell = 0;
    }

    cycle
    {
        current_cell = rand() % 2;
        next_cell = current_cell;
    }
        
        

}