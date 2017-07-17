#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }
    
    // Get path to memory card file
    char* infile = argv[1];
    
    // Open file and store location in inptr
    FILE *inptr = fopen(infile, "rb");
    
    // Check if inptr is valid
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }
    
    int image_num = 0;
    FILE *img = NULL;
    BYTE *buffer = malloc(512 * sizeof(BYTE));
    
    while (fread(buffer, 1, 512, inptr) == 512)
    {
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            image_num ++;
            // If an image file is already being written to, close it
            if (image_num > 1)
            {
                fclose(img);
            }
            
            char img_title[15];
            sprintf(img_title, "%03i.jpg", image_num-1);
            img = fopen(img_title, "w");
        }
        
        if (image_num > 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    
    free(buffer);
}