#include <stdio.h>
#include<cs50.h>
int main(void)
{
    int h;
    do
    {
        printf("Height:");
        h=GetInt();
    }while ((h<0)||(h>23));
    for(int i=1;i<=h;i++)
    {    
        for(int k=h-1;k>i-1;k--)
        {
                printf(" ");
        }
           for(int j=0;j<=i;j++)
           {
             printf("#");
           }
            printf("\n");
    }
}
