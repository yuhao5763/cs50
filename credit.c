#include <cs50.h>
#include <stdio.h>

int calculate_checksum(long card);
string check_type(long card, int checksum);

int main(void)
{
    //prompt for card number
    long card = get_long("Nunmber: ");
    //calculate checksum
    int checksum = calculate_checksum(card);
    //check if the card is valid or not, if valid determine the type of the credit card
    string type = check_type(card, checksum);
    //print out type of the credit card or invalid
    printf("%s\n", type);
}

int calculate_checksum(long card)
{
    int checksum = 0;
    int a, b;
    long temp = card;
    while (temp > 0)
    {
        a = temp % 10;
        temp = (temp - a) / 10;
        b = temp % 10;
        temp = (temp - b) / 10;
        if (b > 4)
        {
            b = (2 * b) - 9;
        }
        else
        {
            b = 2 * b;
        }
        checksum += a + b;
    }
    return checksum;
}

string check_type(long card, int checksum)
{
    string type;
    int digits = 2;
    long temp = card;
    while (temp > 99)
    {
        temp = (temp - (temp % 10)) / 10;
        digits++;
    }
    if ((digits == 13) && ((checksum % 10) == 0) && (temp >= 40 && temp <= 49))
    {
        type = "VISA";
    }
    else if ((digits == 16) && ((checksum % 10) == 0))
    {
        if (temp >= 40 && temp <= 49)
        {
            type = "VISA";
        }
        else if (temp >= 51 && temp <= 55)
        {
            type = "MASTERCARD";
        }
        else
        {
           type = "INVALID";
        }
    }
    else if ((digits == 15) && ((checksum % 10) == 0) && (temp == 34 || temp == 37))
    {
        type = "AMEX";
    }
    else
    {
        type = "INVALID";
    }
    return type;
}
