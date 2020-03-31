#include <stdio.h>
#define MAX 100
#define W 1
#define L 0

int ganha (int dim, char tab[MAX][MAX], char jogador)
{
    int l, c;
    for (l = 0; l < dim && l < MAX; l++)
    {
        for (c = 0; c < dim-2 && c < MAX-2; c++)
        {
            if (tab[l][c] == jogador && tab[l][c+1] == jogador && tab[l][c+2] == jogador)
            {
                return W;
            }
        }
    }
    for (c = 0; c < dim && c < MAX; c++)
    {
        for (l = 0; l < dim-1 && l < MAX-1; l++)
        {
            if (tab[l][c] == jogador && tab[l+1][c] == jogador && tab[l+2][c] == jogador)
            {
                return W;
            }
        }
    }
    for (c = 0; c < dim-2 && c < MAX-2; c++)
    {
        for (l = 0; l < dim-2 && l < MAX-2; l++)
        {
            if ((tab[l][c] == jogador && tab[l+1][c+1] == jogador && tab[l+2][c+2] == jogador) || (tab[l][c+2] == jogador && tab[c+1][l+1] == jogador && tab[l+2][c] == jogador))
            {
                return W;
            }
        }
    }
    return L;
}

int main()
{
    char tab[MAX][MAX];
    int d, n, h, v;
    scanf ("%d%d", &d, &n);
    while (n > 0)
    {
        scanf("%d %d %c", &h, &v, &tab[h][v]);
        n--;
    }
    if (ganha (d, tab, 'x') && !ganha (d, tab, 'o'))
    {
        putchar ('x');
    }
    else if (ganha (d, tab, 'o') && !ganha (d, tab, 'x'))
    {
        putchar ('o');
    }
    else
    {
        putchar ('?');
    }
    return 0;
}