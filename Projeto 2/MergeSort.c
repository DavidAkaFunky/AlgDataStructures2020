#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void merge(int ord[cont_equipas], int flag, int esq, int meio, int dir)
{
    int aux[cont_equipas];
    int i, j, k, cmp;
    for (i = meio+1; i > esq; i--)
        aux[i-1] = ord[i-1];
    for (j = meio; j < dir; j++)
        aux[dir+meio-j] = ord[j+1];
    for (k = esq; k <= dir; k++)
    {
        if (flag)
            cmp = lista_equipas[aux[j]].vitorias < lista_equipas[aux[i]].vitorias;
        else
            cmp = strcmp(lista_equipas[aux[j]].nome, lista_equipas[aux[i]].nome) < 0;
        if (cmp || (lista_equipas[aux[j]].vitorias == lista_equipas[aux[i]].vitorias && aux[j] < aux[i]))
            ord[k] = aux[j--];
        else
            ord[k] = aux[i++];
    }
}

/* Funcao de base do merge sort, incluido a fracao recursiva,
como usado nos slides da unidade curricular. */
void mergesort(int ord[cont_equipas], int flag, int esq, int dir) 
{
    int meio = (dir+esq)/2;
    if (dir <= esq)
        return;
    mergesort(ord, flag, esq, meio);
    mergesort(ord, flag, meio+1, dir);
    merge(ord, flag, esq, meio, dir);
}