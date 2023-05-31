#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = 0;

    while ((height = get_int("Please enter a number between 1 and 8: ")) < 1 || height > 8)
    {
        printf("ERROR: Input out of bounds!\n");
    }

    for (int i = 1; i <= height; i++)
    {
        for (int j = 0; j < (height - i); j++)
        {
            printf(".");
        }
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
