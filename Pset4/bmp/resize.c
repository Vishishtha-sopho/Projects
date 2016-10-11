/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    // check that n is an integer 
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Factor must be an integer\n");
            return 2;
        }
    }
    
    // Check the resize factor
    int fac = atoi(argv[1]);
    if (fac > 100 || fac < 1)
    {
        printf("The resize factor should be a positive integer <= 100.\n");
        return 2;
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
    
    // construct bitmap headers for the outfile
    BITMAPFILEHEADER out_bf;
    BITMAPINFOHEADER out_bi;	
    out_bf = bf;
    out_bi = bi;
    out_bi.biWidth = bi.biWidth * fac;
    out_bi.biHeight = bi.biHeight * fac;

    // determine padding for scanlines

    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding =  (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	
    out_bi.biSizeImage = (out_bi.biWidth * abs(out_bi.biHeight) * sizeof(RGBTRIPLE)) + out_padding * abs(out_bi.biHeight);
	
    // change the file size to reflect the new file size
    out_bf.bfSize = out_bi.biSizeImage + bf.bfOffBits;


    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(out_bi.biHeight); i < biHeight; i++)
    {  
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for(int add = 0; add < fac; add++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
    
        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);

        // then add it to outfile
        for (int k = 0; k < out_padding; k++)
        {    
            fputc(0x00, outptr);
        }

        long offset = bi.biWidth * sizeof(RGBTRIPLE) + in_padding;
        if ((i + 1) % fac != 0) 
        {
            fseek(inptr, -offset, SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
