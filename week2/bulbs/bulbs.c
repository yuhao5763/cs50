#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void convert_string(string message);

int main(void)
{
    // prompt the user for message

    string message = get_string("Message: ");

    // convert string into 8-bit binary numbers, one for each character of the string

    convert_string(message);
}



void convert_string(string message)
{
    int n = strlen(message);
    for (int i = 0; i < n; i++)
    {
        int decimal = message[i];
        int bit[n][8];
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            bit[i][7 - j] = decimal % 2;
            decimal = (decimal - bit[i][7 - j]) / 2;
        }
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            print_bulb(bit[i][k]);
        }
        printf("\n");
    }
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
