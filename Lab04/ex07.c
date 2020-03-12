#include <stdio.h>
#define MAX 80

int main ()
{
    int n, i = 0;
    char tab1[MAX], tab2[MAX], apaga;
    fgets (tab1, MAX, stdin);
    scanf ("%c", &apaga);
    for (n = 0; tab1[n] != '\0'; n++)
    {
        if (tab1[n] == apaga)
        {
            continue;
        }
        tab2[i] = tab1[n];
        i++;
    }
    tab2[i] = '\0';
    printf ("%s", tab2);
    return 0;
}