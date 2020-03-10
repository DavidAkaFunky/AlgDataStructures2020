#include <stdio.h>
#define MAX 80

int main ()
{
    char c, tab[MAX];
    int n;
    for (n = 0; (c = getchar()) != '\n' && c != EOF && n <= MAX-1; n++)
    {
        tab[n] = c;
    }
    tab[n] = '\0';
    printf ("%s", tab);
    return 0;
}