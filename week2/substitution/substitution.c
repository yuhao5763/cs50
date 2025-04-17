#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // checks if the key user types is valid(26 characters) or not, if not, explain with an error
    // message and return from main of a value of 1

    if ((argc == 2) && (strlen(argv[1]) == 26))
    {
        for (int i = 0; i < 26; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check if the key has any duplicated characters, if the key is invalid with duplicate
    // characters, exit with error message if the key is valid and has no duplicated characters,
    // procced the encryption

    for (int i = 0; i < 26; i++)
    {
        for (int j = 1 + i; j < 26 - i; j++)
        {
            if (argv[1][i] == argv[1][j] || argv[1][i] == (argv[1][j] + 32) ||
                argv[1][i] == (argv[1][j] - 32))
            {
                printf("invalid key(duplicate characters)\n");
                return 1;
            }
        }
    }

    // prompt the user for plaintext and encrypts it, the case of each alphabet should be preserve,
    // while non-alphabetical characters should be outputted unchanged.

    string plaintext = get_string("plaintext:  ");
    char ciphertext[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (islower(plaintext[i]))
        {
            ciphertext[i] = argv[1][plaintext[i] - 97];
            ciphertext[i] = (tolower(ciphertext[i]));
        }
        else if (isupper(plaintext[i]))
        {
            ciphertext[i] = argv[1][plaintext[i] - 65];
            ciphertext[i] = (toupper(ciphertext[i]));
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // output cipher text

    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}
