#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_grid(int h);
int main(void)
{
    //promt the user for height(only1-8)
    int h = get_height();
    //print grid of bricks
    print_grid(h);
}


//create get_height function
int get_height(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);
    return h;
}


//create print_grid function


void print_grid(int h)
{
    for (int row = 0; row < h; row++)
    {
        for (int space = 0; space < (h - row - 1); space++)
        {
            printf(" ");
        }
        for (int hash = 0; hash < (row + 1); hash++)
        {
            printf("#");
        }
        printf("\n");

    }
}