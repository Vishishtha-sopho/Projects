/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
    {
        return false;
    }
    else
    {
        int k = 0;
        int i = 0;
        int j = n - 1;
        int mid = (i + j) / 2;
        // TODO: implement a searching algorithm
        while(i <= j)
        {
            if (values[mid] == value)
            {
                k = 1;
                return k;
            } 
            else if(value > values[mid])
            {
                i = mid + 1; 
            }
            else
            {
                j = mid - 1;
            }
            mid = (i + j) / 2;   
        }
        if (k == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{   
    int swap = 0;
    // TODO: implement an O(n^2) sorting algorithm
    for (int i = 0 ; i < ( n - 1 ); i++)
    {
        for (int j = 0 ; j < (n - i - 1); j++)
        {
            if (values[j] > values[j + 1]) 
            {
                swap = values[j];
                values[j] = values[j + 1];
                values[j + 1] = swap;
            }
        }
    }
    for(int i = 0;i < n;i++)
    {
        printf("%i\n",values[i]);
    }
}