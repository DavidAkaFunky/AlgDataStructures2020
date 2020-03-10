#include <stdio.h>
#define MAX 80
#define TRUE 1
#define FALSE 0

int main()
{
    int n, i;
    char tab[MAX];
    scanf ("%s", tab);
    for (n = 0; tab[n+1] != '\0'; n++);
    for (i = 0; i < n; i++, n--)
    {
        if (tab[i] != tab[n])
        {
            printf ("no");
            return 0;
        }
    }
    printf ("yes");
    return 0;
}