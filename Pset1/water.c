#include <stdio.h>
#include<cs50.h>
int main(void)
{
    int min,n;
    printf("Minutes:");
    min=GetInt();
    n=12*min;
    printf("Bottles:%i",n);
}
