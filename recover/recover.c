#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char **argv)
{
    if (argc !=2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open RAW-file.\n");
        return 1;
    }

    FILE *img;
    BYTE buffer[BLOCK];
    int bytes = BLOCK;
    int i = 0;
    char filename[8];
    bool found = false;

    while (bytes == BLOCK)
    {
        bytes = fread(buffer, sizeof(BYTE), BLOCK, card);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (i == 0) // first jpg
                found = true;
            else
                fclose(img);

            sprintf(filename, "%03i.jpg", i);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(card);
                printf("Could not create %s.\n", filename);
                return 1;
            }
            fwrite(buffer, sizeof(BYTE), bytes, img);
            ++i;
        }
        else
            if (found)
                fwrite(buffer, sizeof(BYTE), bytes, img);
    }
    fclose(card);
    fclose(img);
	return 0;
}
