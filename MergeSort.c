#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PROD 10000

int ord[MAX_PROD];

void merge(int ord[MAX_PROD], int left, int m, int right)
{
    int aux[MAX_PROD];
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux[i-1] = ord[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = ord[j+1];
    for (k = left; k <= right; k++)
    {
        if (aux[j] <= aux[i])
            ord[k] = aux[j--];
        else
            ord[k] = aux[i++];
    }
}

void mergesort(int ord[MAX_PROD], int left, int right) 
{
    int m = (right+left)/2;
    if (right <= left)
        return;
    mergesort(ord, left, m);
    mergesort(ord, m+1, right);
    merge(ord, left, m, right);
}

int main ()
{
    int i;
    srand (0);
    for (i = 0; i < MAX_PROD; i++) 
    {
        ord[i] = rand() % 500;
        printf ("%d\n", ord[i]);
    }
    mergesort (ord, 0, MAX_PROD);
    puts ("Ordenado:");
    for (i = 0; i < MAX_PROD; i++) 
        printf ("%d\n", ord[i]);
    return 0;
}