#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define KEYLEN 26

char encode(char character, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution <key>\n");
        return 1;
    }
    string key = argv[1];

    if (strlen(key) != KEYLEN)
    {
        printf("The key must be 26 characters long\n");
        return 1;
    }
    for (int i = 0; i < KEYLEN; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("The key must only contain letters\n");
            return 1;
        }
        for (int j = i + 1; j < KEYLEN; j++)
        {
            if (key[j] == key[i])
            {
                printf("The key must contain every letter only once\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        putchar(encode(plaintext[i], key));
    }
    putchar('\n');

    return 0;
}

char encode(char c, string k)
{
    if (!isalpha(c))
    {
        return c;
    }

    if (isupper(c))
    {
        return toupper(k[c - 'A']);
    }
    else
    {
        return tolower(k[c - 'a']);
    }

}