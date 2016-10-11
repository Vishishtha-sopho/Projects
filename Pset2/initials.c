#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<cs50.h>
int main(void)
{
    string c;
    int n;
    //printf("Enter your name");
    c=GetString();
    n=strlen(c);
    printf("%c",toupper(c[0]));
    for(int i=0;i<n;i++)
    {   
        if(c[i]==32)
        {
        printf("%c",toupper(c[i+1]));
        }
    }
    printf("\n");
}