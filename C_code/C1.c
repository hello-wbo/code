#include "stdio.h"
int main()
{
    int x = 1;
    int a[10][10];
    for (int i = 0; i < 10; i++)
    {
        x++;
        for (int j = 0; j < 10; j++)
        {
            a[i][j] = x++;
        }
    }
    while (x--)
    {
        x--;
    }
}


