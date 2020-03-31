#include <stdio.h>
#include <string.h>
#define MAX 1000

typedef struct
{
    char nome[10];
    float valor;
    float taxa;
}stock;

int main()
{
    int n, i;
    float maior_taxa = 0, maior_valor;
    char maior_nome[10];
    stock tab[MAX];
    scanf ("%d", &n);
    for (i = 0; i < n && i < MAX; i++)
    {
        scanf ("%s%f%f", tab[i].nome, &tab[i].valor, &tab[i].taxa);
        if (tab[i].taxa > maior_taxa)
        {
            maior_taxa = tab[i].taxa;
            maior_valor = tab[i].valor;
            strcpy (maior_nome, tab[i].nome);
        }
    }
    printf ("%s %.2f %.2f", maior_nome, maior_valor, maior_taxa);
    return 0;
}