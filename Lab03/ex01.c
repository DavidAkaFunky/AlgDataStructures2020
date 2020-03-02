#include <stdio.h>

void quadrado (int n)
{
    int i, j;
    if (n >= 2)
    {    
        for (i = 1; i <= n; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf ("%d\t", j+i);
            }
            printf ("\n");
        }
    }
}

int main ()
{
    int n;
    scanf ("%d", &n);
    quadrado (n);
    return 0;
}