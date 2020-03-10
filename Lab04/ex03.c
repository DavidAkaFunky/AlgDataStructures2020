#include <stdio.h>
#define VECMAX 100

int main ()
{
    char tab[VECMAX][VECMAX];
    int n, i, k, ast, maior_ast = 0;
    scanf ("%d", &n);
    for (i = 0; i < n && i < VECMAX; i++)
    {
        scanf ("%d", &ast);
        if (ast > maior_ast)
        {
            maior_ast = ast;
        }
        for (k = 0; k < ast; k++)
        {
            tab[k][i] = '*';
        }
        for (k = ast; k < VECMAX; k++)
        {
            tab[k][i] = ' ';
        }
    }
    for (i = maior_ast; i >= 0; i--)
    {
        for (k = 0; k < n; k++)
        {
            putchar (tab[i][k]);    
        }
        putchar ('\n');
    }
    return 0;
}