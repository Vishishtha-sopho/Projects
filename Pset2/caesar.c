#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, string argv[])
{
    string p;
    int n, k;
    // case when there are too few or more than two command line arguments
    if (argc != 2)
    {
        printf("ENTER PROPER COMMAND LINE ARGUMENT");
        return 1;
    }
    else
    {
        k = atoi(argv[1]);
        p = GetString();
        n = strlen(p);
        for (int i = 0; i < n; i++)
        {
            // to check if the character is an alphabet
            if (isalpha(p[i]))
            {
                // for uppercase
                if (isupper(p[i]))
                {
                    p[i] = (p[i] - 65 + k) % 26;
                    printf("%c",(p[i] + 65));
                }
                // for lowecase
                else
                {
                    p[i] = (p[i] - 97 + k) % 26;
                    printf("%c",(p[i] + 97));
                }
            }
            // unchanged when character is not an alphabet
            else
                printf("%c", p[i]);
        }
        printf("\n");
        return 0;
    }
}
