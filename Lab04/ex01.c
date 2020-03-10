#include <stdio.h>
#define VECMAX 100

int main ()
{
    int n, i, k, ast;
    scanf ("%d", &n);
    for (i = 0; i < n && i < VECMAX; i++)
    {
        scanf ("%d", &ast);
        for (k = 0; k < ast; k++)
        {
            putchar ('*');
        }
        putchar ('\n');
    }
    return 0;
}