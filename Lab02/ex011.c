#include <stdio.h>

int main ()
{
    int x, y;
    printf ("Introduza 2 numeros inteiros: ");
    scanf ("%d %d", &x, &y);
    if (x >= y)
    {
        printf ("%d\n%d", x, y);
    }
    else
    {
        printf ("%d\n%d", y, x);
    }
    return 0;
}