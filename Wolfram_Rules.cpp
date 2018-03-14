//Wolfram Rules (Picture Output)

#include <iostream>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
using namespace std;

#define cycle for(unsigned long long int x = 0; x < size; ++x)
#define current_cell cells[x]
#define right_cell cells[x + 1]
#define left_cell cells[x - 1]
#define next_cell future_cells[x]

int size = -1;
string file_name;
int available_rules[] = {30, 54, 60, 62, 90, 126, 150, 158, 182, 188};
int number_of_rules = sizeof(available_rules) / 4;
int choice = -1;
bool correct_choice = false;

int main(void)
{
    system("Clear");
    void fSetStage(bool *cells, bool *future_cells);
    void fFind(bool *cells, bool *future_cells);
    void fRefresh(bool *cells, bool *future_cells);

    //cout << endl << endl << number_of_rules << endl;
    
    while(size <= 0)
    {
        cout << "Size - ";
        cin >> size;
    }
    if(size % 2 == 0)
        ++size;

    cout << "Name of File(No Spaces) - ";
    cin >> file_name;
    cout << endl << "Available Rules:" << endl;
    for(int i = 0; i < number_of_rules; ++i)
    {
        cout << available_rules[i] << "\t";
    }


    while(!correct_choice)
    {
        cout << endl << "Which Rule Do You Want To Run - ";
        cin >> choice;
        for(int i = 0; i < number_of_rules; ++i)
        {
            if(choice == available_rules[i])
                correct_choice = true;
            
        }
        if(!correct_choice)
            cout << endl << "Please choose one of the available rules.";
    }

    //CREATE PPM FILE
    std::cout << "Making Picture\n";
    ofstream img (file_name + ".ppm");
    img << "P3" << endl;
    //     length       height
    img << size << " " << size / 2 + 2 << endl;
    img << "255" << endl;
    
    int r, g, b;

    //Define the cells and future cells, using the length of the terminal as the size
    bool cells[size];
    bool future_cells[size];

    fSetStage(cells, future_cells);

    cycle
    {
        if (current_cell)
        {
            r = 0, g = 0, b = 0;
        }
        else
        {
            r = 255, g = 255, b = 255;
        }    
        img << r << " " << g << " " << b << endl;
    }

    unsigned long long generation;

    for(generation = 1; generation < size; ++generation)
    {
        cout << generation << endl;
        fFind(cells, future_cells);
        fRefresh(cells, future_cells);

        //Paint Function
        cycle
        {
            if (current_cell)
            {
                r = 0, g = 0, b = 0;
            }
            else
            {
                r = 255, g = 255, b = 255;
            }    
            img << r << " " << g << " " << b << endl;
        }

    }
    cout << "Done" << endl;
    return 0;
}

void fSetStage(bool *cells, bool *future_cells)
{
    cycle
    {
        current_cell = 0;
        next_cell = 0;
    }
    int temp = (size / 2) + 1;

    cells[temp] = true;
    future_cells[temp] = true;
}

void fFind(bool *cells, bool *future_cells)
{
    //Rule 30
    if(choice == 30)
    {
        cycle
        {
            if((!left_cell != !(current_cell || right_cell)))
                next_cell = true;
            else 
                next_cell = 0;
        }
    }
    //Rule 54
    else if(choice == 54)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 60
    else if(choice == 60)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 0;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 62
    else if(choice == 62)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 90
    else if(choice == 90)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 126
    else if(choice == 126)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 150
    else if(choice == 150)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 158
    else if(choice == 158)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 182
    else if(choice == 182)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 0;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    //Rule 188
    else if(choice == 188)
    {
        cycle
        {
            if(left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && current_cell && !right_cell)
                next_cell = 0;
            else if(left_cell && !current_cell && right_cell)
                next_cell = 1;
            else if(left_cell && !current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && right_cell)
                next_cell = 1;
            else if(!left_cell && current_cell && !right_cell)
                next_cell = 1;
            else if(!left_cell && !current_cell && right_cell)
                next_cell = 0;
            else if(!left_cell && !current_cell && !right_cell)
                next_cell = 0;
        }
    }
    
}

void fRefresh(bool *cells, bool *future_cells)
{
    cycle
    {
        current_cell = next_cell;
    }
}

