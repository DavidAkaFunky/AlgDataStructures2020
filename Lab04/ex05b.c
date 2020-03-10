#include <stdio.h>
#define MAX 80

int main ()
{
    char tab[MAX];
    fgets (tab, MAX, stdin);
    printf ("%s", tab);
    return 0;
}