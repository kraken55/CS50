#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char rotate(char letter, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar <key>\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar <key>\n");
            printf("<key> must be a nonnegative integer\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);
    key %= 26;

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        putchar(rotate(plaintext[i], key));
    }
    putchar('\n');

    return 0;
}

char rotate(char c, int k)
{
    if (!isalpha(c))
    {
        return c;
    }

    if (isupper(c))
    {
        return (((c - 'A') + k) % 26) + 'A';
    }
    else
    {
        return (((c - 'a') + k) % 26) + 'a';
    }
}