#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int is_jpeg(uint8_t buffer[512]);
FILE *open_jpeg(int image_count);
int write_block(uint8_t buffer[512], FILE *output);

int main(int argc, char *argv[])
{
    // check the command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover file.\n");
        return 1;
    }

    // open memory card
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("The input file didn't open.\n");
        return 1;
    }

    // initialize varibles
    uint8_t buffer[512];
    int image_counts = 0;
    FILE *output = NULL;

    // reding blocks
    while (fread(buffer, sizeof(uint8_t), 512, input) == 512)
    {
        if (is_jpeg(buffer) == 1)
        {
            if (output != NULL)
            {
                fclose(output);
            }
            output = open_jpeg(image_counts);
            if (output != NULL)
            {
                image_counts++;
            }
        }
        if (output != NULL)
        {
            write_block(buffer, output);
        }
    }
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);
}

int is_jpeg(uint8_t buffer[512])
{
    if (buffer[0] == 0xFF)
    {
        if (buffer[1] == 0xD8)
        {
            if (buffer[2] == 0xFF)
            {
                if ((buffer[3] & 0xF0) == 0XE0)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

FILE *open_jpeg(int image_count)
{
    char filename[8];
    snprintf(filename, sizeof(filename), "%03i.jpg", image_count);
    FILE *output = fopen(filename, "wb");
    if (output == NULL)
    {
        return NULL;
    }
    return output;
}

int write_block(uint8_t buffer[512], FILE *output)
{
    if (output == NULL)
    {
        return 0;
    }
    size_t write = fwrite(buffer, sizeof(uint8_t), 512, output);
    if (write == 512)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
