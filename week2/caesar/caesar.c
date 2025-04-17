#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check if whether it is a single command line argumet, if not output error message and return 1

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //check if the argument is non negative integar

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //cofirm the argument and stores in key

    int key = atoi(argv[1]);

    //determine how many exact position the alphabet is moving

    key = key % 26;

    //prompt the user for plaintext

    string plaintext = get_string("plaintext:  ");

    //determine the length of array ciphertext same as plaintext

    char ciphertext[strlen(plaintext)];

    //encrypts plaintext into cipher text, case of alphabet should be reserved, and punctuations remain as original

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]) == 0)
        {
            ciphertext[i] = plaintext[i];
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = (plaintext[i] - 97 + key) % 26 + 97;
        }
        else
        {
            ciphertext[i] = (plaintext[i] - 65 + key) % 26 + 65;
        }
    }

    //out put the ciphertext

    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}
