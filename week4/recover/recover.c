#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
    // check if only 1 command-line argument, if not, return 1 and printf usage

    if (argc != 2)
    {
        printf("usage: ./recover 'name of the forensic image'\n");
        return 1;
    }

    // fopen argv[1], if returns NULL, inform user the usage and main return 1

    FILE *recover_file = fopen(argv[1], "r");
    if (recover_file == NULL)
    {
        printf("failed to open the memory card\n");
        return 1;
    }

    // proceed to recovering jpg

    const int block_bytes = 512;
    uint8_t *BLOCK = malloc(block_bytes * sizeof(uint8_t));
    while (true)
    {
        if (fread(BLOCK, sizeof(uint8_t), block_bytes, recover_file) == 0)
        {
            printf("jpg undetected\n");
            fclose(recover_file);
            free(BLOCK);
            return 2;
        }
        if (BLOCK[0] == 0xff && BLOCK[1] == 0xd8 && BLOCK[2] == 0xff && (BLOCK[3] & 0xf0) == 0xe0)
        {
            printf("jpg detected\n");
            break;
        }
    }
    int jpg_index = 0;
    char filename[8];
    FILE *new_jpg = NULL;
    do
    {
        if (BLOCK[0] == 0xff && BLOCK[1] == 0xd8 && BLOCK[2] == 0xff && (BLOCK[3] & 0xf0) == 0xe0)
        {
            if (jpg_index > 0)
                fclose(new_jpg);
            if (jpg_index > 999)
            {
                printf("jpg index over 999\n");
                fclose(recover_file);
                free(BLOCK);
                return 3;
            }
            sprintf(filename, "%03i.jpg", jpg_index);
            jpg_index++;
            new_jpg = fopen(filename, "w");
            if (new_jpg == NULL)
            {
                printf("unable to open new_jpg\n");
                fclose(recover_file);
                free(BLOCK);
                return 4;
            }
        }
        fwrite(BLOCK, sizeof(uint8_t), block_bytes, new_jpg);
    }
    while (fread(BLOCK, sizeof(uint8_t), block_bytes, recover_file));
    fclose(new_jpg);
    fclose(recover_file);
    free(BLOCK);
}
