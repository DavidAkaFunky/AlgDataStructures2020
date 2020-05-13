/* Ficheiro: Projeto2.c
 * Nome: David Emanuel Silva Belchior -- Instituto Superior Tecnico -- LEIC-A -- Numero 95550 
 * Descricao: Sistema de gestao de base de dados de jogos amigaveis de futebol, com diversas
 * funcoes aplicadas sobre esta base de dados.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Listas.h"
#include "Hash.h"
#include "MergeSort.h"

#define MAX 1024
#define HASH 151

typedef struct
{
    char* nome;
    int vitorias;
} Equipa;

typedef struct
{
    char* nome;
    Equipa eq_casa;
    Equipa eq_fora;
    int golos_casa;
    int golos_fora;
} Jogo;

typedef struct node
{
    Item item; /* Completar abstracao */
    struct node *prox;
}* link;

char comm; /* Inicializacao do caracter usado como comando do programa. */
int cont_linha = 0;
int cont_equipas = 0;
Equipa* hash_table_equipas[HASH];
Equipa* lista_equipas;
Jogo* hash_table_jogos[HASH];
Jogo* lista_jogos;

void adiciona_jogo()
{
    char nome_jogo[MAX], eq_casa[MAX], eq_fora[MAX];
    int golos_casa, golos_fora;
    cont_linha++;
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:", nome_jogo, eq_casa, eq_fora);
    if (procura(nome_jogo))
        printf("%d Jogo existente.\n", cont_linha);
    else if (!(procura(eq_casa) && procura(eq_fora)))
        printf("%d Equipa inexistente.\n", cont_linha);
    else
    {
        Jogo novo_jogo = (Jogo) malloc(sizeof(Jogo));
        int hash = hash(nome_jogo);
        scanf("%d:%d", &golos_casa, &golos_fora);
        novo_jogo.nome = nova_str(nome_jogo);
        novo_jogo.eq_casa = nova_str(eq_casa);
        novo_jogo.eq_fora = nova_str(eq_fora);
        novo_jogo.golos_casa = golos_casa;
        novo_jogo.golos_fora = golos_fora;
        insere_fim(hash_table_jogos[hash], novo_jogo);
        insere_fim(lista_jogos, novo_jogo);
        if (golos_casa > golos_fora)
            novo_jogo.eq_casa.vitorias++;
        else if (golos_fora > golos_casa)
            novo_jogo.eq_fora.vitorias++;
    }
}

char* nova_str(char* str_orig, char* nova_str)
{
    char* nova_str = (char*) malloc(sizeof(str_orig)+1);
    strcpy(nova_str, str_orig);
    return nova_str;
}

void adiciona_equipa()
{
    char nome_equipa[MAX];
    cont_linha++;
    scanf(" %[^:\n]", nome_equipa);
    if (!procura(nome_equipa))
        printf("%d Equipa inexistente.\n", cont_linha);
    else
    {
        Equipa nova_equipa = (Equipa) calloc(sizeof(Equipa));
        int hash = hash(nome_equipa);
        nova_equipa.nome = nova_str(nova_equipa.nome, nome_equipa);
        insere_fim(hash_table_equipas[hash], nome_equipa);
        cont_equipas++;
    }
}

void procura_jogo()
{
    char nome[MAX];
    cont_linha++;
    scanf(" %s", nome);
    if (procura(hash_table_jogos, nome, HASH))
        printf("%d %s", cont_linha, nome);
    else
        printf("%d Jogo inexistente.\n", cont_linha);
}

void procura_equipa()
{
    char nome[MAX];
    Equipa equipa;
    cont_linha++;
    scanf(" %s", nome);
    if ((equipa = procura(hash_table_jogos, nome, HASH)))
        printf("%d %s %d\n", cont_linha, equipa -> nome, equipa -> vitorias);
}

void apaga_jogo()
{
    char nome[MAX];
    cont_linha++;
    scanf(" %s", nome);
    if (!(procura(hash_table_jogos, nome, HASH)))
        printf("%d Jogo inexistente.\n", cont_linha);
    else
    {
        int hash = hash(nome, HASH);
        Jogo* x = hash_table_jogos[hash];
        apaga(x, nome);
        x = lista_jogos;
        apaga(x, nome);
    }
}

void encontra_melhores_equipas()
{
    if (lista_equipas)
    {
        int i, j, ord[cont_equipas];
        cont_linha++;
        for (i = 0; i < cont_equipas; i++) /* Copia dos indices do array dos produtos da encomenda ide para os ordenar depois. */
            ord[i] = i;
        mergesort (ord, 0, 0, cont_equipas-1); /* Merge sort do array dos indices da forma descrita no comentario do cabecalho. */
        mergesort (ord, 1, 0, cont_equipas-1);
        printf("%d Melhores %d\n", cont_linha, ord[0]);
        for (j = 0; j < cont_equipas && ord[j] == ord[0]; j++)
        printf ("%d * %s\n", cont_linha, lista_equipas[ord[j]].nome);
    }
}

void altera_score()
{
    char nome_jogo[MAX];
    Jogo jogo;
    cont_linha++;
    scanf(" %[^:\n]:", nome_jogo);
    if (!(jogo = procura(nome_jogo)))
        printf("%d Jogo inexistente.\n", cont_linha);
    else
    {
        if (jogo.golos_casa > jogo.golos_fora)
            jogo.eq_casa.vitorias--;
        else if (jogo.golos_fora > jogo.golos_casa)
            jogo.eq_fora.vitorias--;
        scanf("%d:%d", &jogo.golos_casa, &jogo.golos_fora);
        if (jogo.golos_casa > jogo.golos_fora)
            jogo.eq_casa.vitorias++;
        else if (jogo.golos_fora > jogo.golos_casa)
            jogo.eq_fora.vitorias++;
    }
}

void listar_jogos()
{
    Jogo* x = lista_jogos;
    cont_linha++;
    for (; x; x = x -> prox)
        printf("%d %s %s %s %d %d\n", cont_linha, x -> nome, x -> eq_casa, x -> eq_fora, x -> golos_casa, x -> golos_fora);
}

void destroi_estruturas()
{
    destroi_hash_table(hash_table_equipas, HASH);
    destroi_hash_table(hash_table_jogos, HASH);
    destroi(lista_equipas);
    destroi(lista_jogos);
}

/* Recebe uma letra como comando e invoca a funcao correspondente, como
descrito no enunciado do projeto. O comando 'x' encerra o programa. */
int main()
{
    inicializa_estruturas();
    while ((comm = getchar()) != 'x') /* Introducao do comando. */
    {
        switch (comm)
        {
            case 'a':
                adiciona_jogo();
                break;
            case 'A':
                adiciona_equipa();
                break;
            case 'l':
                listar_jogos();
                break;
            case 'p':
                procura_jogo();
                break;
            case 'P':
                procura_equipa();
                break;
            case 'r':
                apaga_jogo();
                break;
            case 's':
                altera_score();
                break;
            case 'g':
                encontra_melhores_equipas();
                break;
        }
    }
    destroi_estruturas();
    return 0;
}