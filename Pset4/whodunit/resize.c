/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy scale-factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int scale = atoi(argv[1]);
    
    // Check if scale factor is valid
    if (scale < 1 || scale > 100)
    {
        fprintf(stderr, "Scale factor is invalid");
        return 1;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_width = bi.biWidth;
    
    // Modify file headers
    bi.biWidth *= scale;
    bi.biHeight *= scale;
    
    // Determine the size out outpadding for padding the image and determining image size
    int out_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Modify image headers
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + out_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(bf) + sizeof(bi);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    int iter = 1;
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        fpos_t pos;
        fgetpos(inptr, &pos);   // Remember the location of the start of the scanline
        
        // iterate over pixels in scanline
        for (int j = 0; j < old_width; j++)
        {
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            for (int k = 0; k < scale; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); 
            }
        }
        
        // skip over padding in original file
        fseek(inptr, padding, SEEK_CUR);

        // Add in padding into resized file
        for (int k = 0; k < out_padding; k++)
        {
            fputc(0x00, outptr);
        }
        
        // To resize vertically, several lines must be repeated. Iter keeps track of how many
        // times the line has been printed. If it is less than the scale facter, inptr is reset
        // back to the start of the previous line. Otherwise it is reset to 1 for the next line. 
        if (iter < scale)
        {
            fsetpos(inptr, &pos);
            iter ++;
        }
        else
        {
            iter = 1;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
