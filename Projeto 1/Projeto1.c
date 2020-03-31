/* David Emanuel Silva Belchior -- LEIC-A -- Numero 95550 */
#include <stdio.h>
#include <string.h>
#define NO 0
#define YES 1
#define MAX_DADOS 3
#define MAX_NOME 64
#define MAX_PESO 200
#define MAX_ENC 500
#define MAX_PROD 10000

void comm_a(int contador, char nomes[MAX_PROD][MAX_NOME], int produtos[MAX_PROD][MAX_DADOS])
{
    scanf ("%[^:]:%d:%d:%d", nomes[contador], &produtos[contador][0], &produtos[contador][1], &produtos[contador][2]);
    printf ("Novo produto %d.\n", contador);
}

void comm_q (int contador, int produtos[MAX_PROD][MAX_DADOS])
{
    char prod[MAX_NOME];
    int idp, qtd;
    fgets (prod, MAX_NOME, stdin);
    scanf ("%d", &idp);
    if (idp <= contador)
    {
        scanf ("%d", &qtd);
        produtos[idp][2] += qtd;
    }
    else
    {
        printf ("Impossivel adicionar produto %s ao stock. Produto inexistente.\n", prod);
    }
}

void comm_N (int contador, int encomendas[MAX_ENC][MAX_PROD])
{
    int i;
    for (i = 0; i < MAX_PROD; i++)
    {
        encomendas[contador][i] = 0;
    }
    printf ("Nova encomenda %d.\n", contador);
}

void comm_A (int contador_nome, int contador_enc, int produtos[MAX_PROD][MAX_DADOS], int encomendas[MAX_ENC][MAX_PROD])
{
    int ide, idp, qtd;
    scanf ("%d:%d:", &ide, &idp);
    if (ide > contador_enc)
    {
        printf ("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else
    {
        if (idp > contador_nome)
        {
            printf ("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
            scanf ("%d", &qtd);
            if (produtos[idp][2] < qtd)
            {
                printf ("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", idp, ide);
            }
            else if (produtos[idp][1] * qtd > MAX_PESO)
            {
                printf ("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", idp, ide);
            }
            else
            {
                encomendas[ide][idp] += qtd;
                produtos[idp][2] -= qtd;
            }
        }
    }
}

void comm_r (int contador_nome, int produtos[MAX_PROD][MAX_DADOS])
{
    int idp, qtd;
    scanf ("%d", &idp);
    if (idp > contador_nome)
    {
        printf ("Impossivel remover stock do produto %d. Produto inexistente.\n", idp);
    }
    else
    {
        scanf (":%d", &qtd);
        if (qtd > produtos[idp][2])
        {
            printf ("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qtd, idp);
        }
        else
        {
            produtos[idp][2] -= qtd;
        }
    }
    
}

void comm_R (int contador_nome, int contador_enc, int produtos[MAX_PROD][MAX_DADOS], int encomendas[MAX_ENC][MAX_PROD])
{
    int ide, idp;
    scanf ("%d:%d:", &ide, &idp);
    if (ide > contador_enc)
    {
        printf ("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
    }
    else
    {
        if (idp > contador_nome)
        {
            printf ("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        }
        else
        {
            produtos[idp][2] += encomendas[ide][idp];
            encomendas[ide][idp] = 0;
        }
    }
}

void comm_C (int contador_enc, int produtos[MAX_PROD][MAX_DADOS], int encomendas[MAX_ENC][MAX_PROD])
{
    int ide, i, total = 0;
    scanf ("%d", &ide);
    if (ide > contador_enc)
    {
        printf ("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
        for (i = 0; i < MAX_PROD; i++)
        {
            total += encomendas[ide][i] * produtos[i][0];
        }
    }
    printf("Custo da encomenda %d %d.", ide, total);
}

void comm_p (int contador_nome, int produtos[MAX_PROD][MAX_DADOS])
{
    int idp, preco;
    scanf ("%d", &idp);
    if (idp > contador_nome)
    {
        printf ("Impossivel alterar preco do produto %d. Produto inexistente.\n", idp);
    }
    else
    {
        scanf (":%d", &preco);
        produtos[idp][0] = preco;
    }
}

void comm_E (int contador_nome, int contador_enc, char nomes[MAX_PROD][MAX_NOME], int encomendas[MAX_ENC][MAX_PROD])
{
    int ide, idp;
    scanf ("%d", &ide);
    if (ide > contador_enc)
    {
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
        scanf (":%d", &idp);
        if (idp > contador_nome)
        {
            printf ("Impossivel listar produto %d. Produto inexistente.\n", idp);
        }
        else
        {
            printf ("%s %d", nomes[idp], encomendas[ide][idp]);
        }
    }
}

void comm_m (int contador_nome, int contador_enc, int encomendas[MAX_ENC][MAX_PROD])
{
    int idp, ide, ide_max, qtd = 0;
    scanf ("%d", &idp);
    if (idp > contador_nome)
    {
        printf ("Impossivel listar maximo do produto %d. Produto inexistente.\n", idp);
    }
    else
    {
        for (ide = 0; ide <= contador_enc; ide++)
        {
            if (encomendas[ide][idp] > qtd)
            {
                ide_max = ide;
                qtd = encomendas[ide][idp];
            }
        }
        if (qtd > 0)
        {
            printf ("Maximo produto %d %d %d\n", idp, ide_max, qtd);
        }
    }
}

void bubble (int flag, int contador, int produtos[MAX_PROD][MAX_DADOS], char nomes[MAX_PROD][MAX_NOME], int ord[MAX_PROD])
{
    int i, j, aux, cmp;
    for (i = 0; i < contador; i++) /* Ordenar arrays com bubble sort */
    {
        for (j = 0; j < contador - i; j++)
        {
            if (flag)
            {
                cmp = produtos[ord[j]][0] > produtos[ord[j+1]][0];
            }
            else
            {
                cmp = strcmp(nomes[ord[j]], nomes[ord[j+1]]);
            }
            if (cmp)
            {
                aux = ord[j];
                ord[j] = ord[j+1];
                ord[j+1] = aux;
            }
        }
    }
}

void comm_l (int contador_nome, char nomes[MAX_PROD][MAX_NOME], int produtos[MAX_PROD][MAX_DADOS], int produtos_ord[MAX_PROD])
{
    int i;
    puts ("Produtos\n");
    for (i = 0; i <= contador_nome; i++) /* Copiar arrays para os ordenar depois */
    {
        produtos_ord[i] = i;
    }
    bubble (YES, contador_nome, produtos, nomes, produtos_ord);
    for (i = 0; i <= contador_nome; i++) /* Imprimir dados */
    {
        printf ("* %s %d %d\n", nomes[produtos_ord[i]], produtos[produtos_ord[i]][0], produtos[produtos_ord[i]][2]);
    }
}

void comm_L (int contador_enc, int contador_nome, int produtos[MAX_PROD][MAX_DADOS], char nomes[MAX_PROD][MAX_NOME], int encomendas[MAX_ENC][MAX_PROD], int encomenda_ord[MAX_PROD])
{
    int ide, i, contador = 0;
    scanf ("%d", &ide);
    if (ide > contador_enc)
    {
        printf ("Impossivel listar encomenda %d. Encomenda inexistente.\n", ide);
    }
    else
    {
        printf ("Encomenda %d\n", ide);
        for (i = 0; i < MAX_PROD; i++) /* Copiar arrays para os ordenar depois */
        {
            if (encomendas[ide][i] != 0)
            {
                encomenda_ord[contador] = i;
                contador++;
            }
        }
        bubble (YES, contador, produtos, nomes, encomenda_ord);
        for (i = 0; i <= contador_nome; i++) /* Imprimir dados */
        {
            printf ("* %s %d %d\n", nomes[encomenda_ord[i]], produtos[encomenda_ord[i]][0], encomendas[ide][encomenda_ord[i]]);
        }
    }
}

int main()
{
    char comm, nomes[MAX_PROD][MAX_NOME] = {{'0'}};
    int contador_nome = 0, contador_enc = 0, produtos[MAX_PROD][MAX_DADOS] = {0}, encomendas[MAX_ENC][MAX_PROD] = {0}, ord[MAX_PROD] = {0};
    while ((comm = getchar()) != 'x') /* Introducao do comando */
    {
        switch (comm)
        {
            case 'a':
                comm_a (contador_nome, nomes, produtos);
                contador_nome++;
                break;
            case 'q':
                comm_q (contador_nome, produtos);
                break;
            case 'N':
                comm_N (contador_enc, encomendas);
                contador_enc++;
                break;
            case 'A':
                comm_A (contador_nome, contador_enc, produtos, encomendas);
                break;
            case 'r':
                comm_r (contador_nome, produtos);
                break;
            case 'R':
                comm_R (contador_nome, contador_enc, produtos, encomendas);
                break;
            case 'C':
                comm_C (contador_enc, produtos, encomendas);
                break;
            case 'p':
                comm_p (contador_nome, produtos);
                break;
            case 'E':
                comm_E (contador_nome, contador_enc, nomes, encomendas);
                break;
            case 'm':
                comm_m (contador_nome, contador_enc, encomendas);
                break;
            case 'l':
                comm_l (contador_nome, nomes, produtos, ord);
                break;
            case 'L':
                comm_L (contador_enc, contador_nome, produtos, nomes, encomendas, ord);
                break;
        }
    }
    return 0;
} 