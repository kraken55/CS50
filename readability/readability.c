#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int CountLetters(string text);
int CountWords(string text);
int CountSentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int nLetters = 0, nWords = 0, nSentences = 0;

    nLetters = CountLetters(text);
    nWords = CountWords(text);
    nSentences = CountSentences(text);

    /*
    printf("%d\n", nLetters);
    printf("%d\n", nWords);
    printf("%d\n", nSentences);
    */

    float L = (nLetters / (float) nWords) * 100;
    float S = (nSentences / (float) nWords) * 100;

    /*
    printf("L: %f\n", L);
    printf("S: %f\n", S);
    */

    float grade = round(0.0588 * L - 0.296 * S - 15.8);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade);
    }

    return 0;
}

int CountLetters(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isalpha(s[i]))
        {
            count++;
        }
    }

    return count;
}

int CountWords(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isspace(s[i]))
        {
            count++;
        }
    }
    count++; // Because every word has a space before it, except the first one

    return count;
}

int CountSentences(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count++;
        }
    }

    return count;
}