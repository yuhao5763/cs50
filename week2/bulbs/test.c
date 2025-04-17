#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;
int decimal;

void print_bulb(int bit);
int convert_string(int integar);

int main(void)
{
    // prompt the user for message

    string message = get_string("Message: ");

    // convert string into 8-bit binary numbers, one for each character of the string

    int n = strlen(message);
    int bit[n][BITS_IN_BYTE];
    for (int i = 0; i < n; i++)
    {
        decimal = message[i];
        for(int j = 0; j < BITS_IN_BYTE; j++)
        {
            bit[i][(BITS_IN_BYTE-1)-j] = convert_string(decimal);
        }
    }
    // output the bits and also into lightbulbs

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            printf("%i", bit[i][j]);
        }
        printf("\n");
    }

    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            print_bulb(bit[j][k]);
        }
        printf("\n");
    }
}



int convert_string(int integar)
{
    int bit = decimal % 2;
    decimal = (decimal - bit) / 2;
    return bit;
}
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
