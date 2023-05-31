#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("error: wrong usage\n");
        printf("usage: ./recover data\n");
        return 1;
    }

    // Open memory card
    FILE *memoryCard = fopen(argv[1], "r");
    if (memoryCard == NULL)
    {
        printf("Error: couldn't open memory card.\n");
        return 1;
    }

    FILE *img = NULL;
    int fileNo = 0;

    BYTE buffer[BLOCK_SIZE];
    char filename[8];
    bool injpg = false;
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, memoryCard) == BLOCK_SIZE)
    {
        // Checks if start of chunk mathes start of jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if we were already inside a jpg file, close the old one
            if (injpg)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", fileNo);
            img = fopen(filename, "w");
            injpg = true;
            fileNo++;
        }
        if (injpg)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }

    // Close files
    fclose(memoryCard);
    fclose(img);
}