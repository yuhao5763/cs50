#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // prompt the user for string of text

    string text = get_string("Text: ");

    // count the number of letters, words, and sentences in the text

    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    // determine the grade level of the text computed by Coleman-Liau formula, rouded to the nearest
    // integer

    int index =
        round(0.0588 * ((letters / words) * 100) - 0.296 * ((sentences / words) * 100) - 15.8);

    // print the grade level out, output "Grade 16+" if greater than 16, "Before Grade 1" if less
    // than 1

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 1;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == 32)
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}
