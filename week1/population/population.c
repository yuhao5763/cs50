#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int ss;
    do
    {
        ss = get_int("start size (must >= 9):");
    }
    while (ss < 9);
    // Prompt for end size
    int es;
    do
    {
        es = get_int("end size (must greater or equal than start size):");
    }
    while (es < ss);
    // Calculate number of years until we reach threshold
    int Years = 0;
    while (ss < es)
    {
        ss = ss + (ss - (ss % 3)) / 3 - (ss - (ss % 4)) / 4;
        Years++;
    }
    // Print number of years
    printf("Years: %i\n", Years);
}
