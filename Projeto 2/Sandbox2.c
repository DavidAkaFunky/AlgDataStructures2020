#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1024
#define HASH 151

typedef struct
{
    char* nome;
    int vitorias;
} equipa;

typedef struct node_equipa
{
    equipa equipa;
    struct node_equipa *prox, *ant;
} node_equipa;

typedef struct
{
    struct node_equipa *inicio, *fim;
} lista_equipas;

int cont_linha = 0;

int hash(char *v, int M)
{
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;
    return h;
}

equipa cria_equipa(char* nome)
{
    equipa nova_equipa;
    nova_equipa.nome = (char*) malloc(sizeof(nome)+1);
    strcpy(nova_equipa.nome, nome);
    nova_equipa.vitorias = 0;
    return nova_equipa;
}

int procura_equipa_hash(int cont_linhas, char* nome, lista_equipas** hash_table_equipas)
{
    int hash_nome = hash(nome, HASH);
    lista_equipas* aux = hash_table_equipas[hash_nome];
    while (aux -> inicio)
    {
        if (!strcmp(aux -> inicio -> equipa.nome, nome))
        {
            if (cont_linhas)
                printf("%d %s %d\n", cont_linhas, aux -> inicio -> equipa.nome, aux -> inicio -> equipa.vitorias);
            return 1;
        }
        aux -> inicio = aux -> inicio -> prox;
    }
    return 0;
}

lista_equipas* cria_lista_equipas()
{
    lista_equipas* novo = malloc(sizeof(lista_equipas));
    novo -> inicio = novo -> fim = NULL;
    return novo;
}

void cria_hash_table_equipas(lista_equipas** hash_table_equipas, int hash)
{
    int i;
    for (i = 0; i < hash; i++)
    {
        hash_table_equipas[i] = cria_lista_equipas();
    }
}

void insere_fim_equipa(lista_equipas* l, equipa nova_equipa)
{
    node_equipa* n = malloc(sizeof(node_equipa));
    n -> prox = NULL;
    n -> ant = l -> fim;
    n -> equipa = nova_equipa;
    if (l -> fim)
        l -> fim -> prox = n;
    l -> fim = n;
    if (!l -> inicio)
        l -> inicio = n;
}

void insere_equipa_hash(lista_equipas** hash_table_equipas, equipa nova_equipa)
{
    int hash_nome = hash(nova_equipa.nome, HASH);
    insere_fim_equipa(hash_table_equipas[hash_nome], nova_equipa);
}

void destroi_lista_equipas(lista_equipas* l)
{
    while (l -> inicio)
    {
        node_equipa* aux = l -> inicio -> prox;
        free(l -> inicio -> equipa.nome);
        free(l -> inicio);
        l -> inicio = aux;
    }
    free(l);
}

void destroi_hash_table_equipas(lista_equipas** hash_table_equipas, int hash)
{
    int i;
    for (i = 0; i < hash; i++)
    {
        destroi_lista_equipas(hash_table_equipas[i]);
    }
}

void imprime_equipas(lista_equipas** hash_table_equipas, int hash)
{
    int i;
    for (i = 0; i < hash; i++)
    {
        lista_equipas* aux = hash_table_equipas[i];
        while (aux -> inicio)
        {
            printf("%s %d\n", aux -> inicio -> equipa.nome, aux -> inicio -> equipa.vitorias);
            aux -> inicio = aux -> inicio -> prox;
        }
    }
}

void adiciona_equipa(lista_equipas** hash_table_equipas)
{
    char nome_equipa[MAX];
    cont_linha++;
    scanf(" %[^:\n]", nome_equipa);
    if (procura_equipa_hash(0, nome_equipa, hash_table_equipas))
        printf("%d equipa existente.\n", cont_linha);
    else
    {
        equipa nova_equipa = cria_equipa(nome_equipa);
        insere_equipa_hash(hash_table_equipas, nova_equipa);
    }
}

void procura_equipa(lista_equipas** hash_table_equipas)
{
    char nome_equipa[MAX];
    equipa* equipa;
    cont_linha++;
    scanf(" %s", nome_equipa);
    if ((equipa = procura_equipa_hash(nome_equipa, hash_table_equipas)))
        printf("%d %s %d\n", cont_linha, equipa -> nome, equipa -> vitorias);
    else
        printf("%d Equipa inexistente.\n", cont_linha);
}

int comparador(const void* a, const void* b)
{
    return strcmp((char*) a, (char*) b);
}

void encontra_melhores_equipas(lista_equipas** hash_table_equipas)
{
    int max = -1, num_max = 0, i, j = 0;
    char** melhores_equipas;
    if (cont_equipas)
    {
        for (i = 0; i < HASH; i++)
        {
            node_equipa* aux = hash_table_equipas[i] -> inicio;
            while (aux)
            {
                if (aux -> equipa.vitorias > max)
                {
                    max = aux -> equipa.vitorias;
                    num_max = 1;
                }
                else if (aux -> equipa.vitorias == max)
                {
                    num_max++;
                } 
                aux = aux -> prox;
            }
        }
        melhores_equipas = (char**) malloc (sizeof(char*) * num_max);
        for (i = 0; i < HASH; i++)
        {
            node_equipa* aux = hash_table_equipas[i] -> inicio;
            while (aux)
            {
                if (aux -> equipa.vitorias == max)
                {
                    melhores_equipas[j] = aux -> equipa.nome;
                    printf("%s %s\n", melhores_equipas[j++], aux->equipa.nome);
                } 
                aux = aux -> prox;
            }
        }
        qsort(melhores_equipas, num_max, sizeof(char*), comparador);
        printf("%d Melhores %d\n", ++cont_linha, max);
        for (i = 0; i < j; i++)
        {
            printf("%d * %s\n", cont_linha, melhores_equipas[i]);
        }
        free(melhores_equipas);
    }
}

int main()
{
    /*lista_jogo* lista_jogos = nova_lista_jogos();
    lista_jogo* hash_table_jogos[HASH] = cria_hash_table_jogos(HASH);*/
    lista_equipas** hash_table_equipas = (lista_equipas**) malloc (sizeof(lista_equipas*)*HASH);
    char comm;
    cria_hash_table_equipas(hash_table_equipas, HASH);
    printf("Debug");
    while ((comm = getchar()) != 'x') /* Introducao do comando. */
    {
        switch (comm)
        {
            /*case 'a':
                adiciona_jogo();
                break;*/
            case 'A':
                adiciona_equipa(hash_table_equipas);
                break;
            /*case 'l':
                listar_jogos();
                break;
            case 'p':
                procura_jogo();
                break;*/
            case 'P':
                procura_equipa(hash_table_equipas);
                break;
            /*case 'r':
                apaga_jogo();
                break;
            case 's':
                altera_score();
                break;*/
            case 'g':
                encontra_melhores_equipas(hash_table_equipas);
                break;
        }
    }
    destroi_hash_table_equipas(hash_table_equipas, HASH);
    free(hash_table_equipas);
    return 0;
}