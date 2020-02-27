#include <stdio.h>

int main ()
{
    int x, i;
    printf ("Introduza um numero inteiro: ");
    scanf("%d", x);
    for (i = 1, i <= x, i++)
    {
        printf("%d\n", i)
    }
    return 0;
}