#include<stdio.h>
#include<math.h>
#include<cs50.h>
int main(void)
{
    int c,x=0;
    float ch;
    do
    {
     printf("O hai! How much change is owed?");
     ch=GetFloat();
     c = (int)roundf(ch*100);  
    }while(ch<0);
    while(c>0)
    {
        if(c>=25)
    {
        c-=25;
        x+=1;;
    }
    else if(c>=10)
    {
        c-=10;
        x+=1;
    }
    else if(c>=5)
    {
        c-=5;
        x+=1;;
    }
    else if(c>=1)
    {
        c-=1;
        x+=1;
    }
}
printf("%i\n",x);
}