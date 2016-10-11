/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    // TODO
    //open input file
    FILE* pics = fopen("card.raw", "r");
    if (pics == NULL)
    {
        fclose(pics);
        printf("Could not open file\n");
        return 1;
    }


    FILE* out_pic;
    
    BYTE check[3]={0xff, 0xd8, 0xff};
    // open output file
    /*FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }*/
    int count = 0;
    int open=0;
    BYTE buff[512];
    BYTE test[4];
    
    fread(buff, 512, 1, pics);

    while(fread(buff, 512, 1, pics)>0)
    {
        for (int i = 0; i < 3; i++)
        {
            test[i]=buff[i];
        }
        if(memcmp(check, test, 3) == 0)
        {
            char rec[8];
            sprintf(rec, "%03d.jpg", count);
            if(open == 0)
			{
			    out_pic = fopen(rec, "w");
				fwrite(buff, sizeof(buff), 1, out_pic);
				open = 1;
			}
			if(open == 1)
			{
				fclose(out_pic);
				out_pic = fopen(rec, "w");
				fwrite(buff, sizeof(buff), 1, out_pic);
				count++;
			}
        }
		else
		{
			if(open == 1)
			{
				fwrite(buff, sizeof(buff), 1, out_pic);
			}
		}
    
    }
    if(out_pic)
    {
      fclose(out_pic);
    }

		fclose(pics);
		return 0;
}
