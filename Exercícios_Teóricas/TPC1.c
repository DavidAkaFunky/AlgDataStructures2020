#include <stdio.h>

int main ()
{   
    int x;
    int soma = 0;
    scanf ("%d", &x);
    while (x >= 0)
    {
        soma ++;
        scanf ("%d", &x);
    }
    printf ("%d\n", soma);
    return 0;
}