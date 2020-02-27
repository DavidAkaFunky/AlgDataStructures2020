#include <stdio.h>

int main ()
{
    int x, y, z;
    printf ("Introduza 3 numeros inteiros: ");
    scanf ("%d %d %d", &x, &y, &z);
    if (x <= y && x <= z)
    {
        printf ("%d", x);
        if (y <= z)
        {
            printf ("%d %d", y, z);
        }
        else
        {
            printf ("%d %d", z, y)
        }
    }
    if (y <= x && y <= z)
    {
        printf ("%d", y);
        if (x <= z)
        {
            printf ("%d %d", x, z);
        }
        else
        {
            printf ("%d %d", z, x)
        }
    }
    else
    {
        printf ("%d", z);
        if (x <= y)
        {
            printf ("%d %d", x, y);
        }
        else
        {
            printf ("%d %d", y, x)
        }
    }
    return 0;
}