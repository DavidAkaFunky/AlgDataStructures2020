#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Equipas.h"
#include "Jogos.h"
#include "Hash.h"

void adiciona_jogo(int cont_linhas, lista_equipas** hash_table_equipas, lista_jogos* lst_jogos, lista_jogos** hash_table_jogos)
{
    char nome_jogo[MAX];
    scanf(" %[^:\n]", nome_jogo);
    if (procura_jogo_hash(nome_jogo, hash_table_jogos) != NULL)
        printf("%d Jogo existente.\n", cont_linhas);
    else
    {
        equipa *eq_casa, *eq_fora;
        char nome_casa[MAX], nome_fora[MAX];
        scanf(":%[^:\n]:%[^:\n]", nome_casa, nome_fora);
        if (!((eq_casa = procura_equipa_hash(nome_casa, hash_table_equipas)) && (eq_fora = procura_equipa_hash(nome_fora, hash_table_equipas))))
            printf("%d Equipa inexistente.\n", cont_linhas);
        else
        {
            int golos_casa, golos_fora;
            jogo* novo_jogo;
            scanf(":%d:%d", &golos_casa, &golos_fora);
            novo_jogo = cria_jogo(nome_jogo, eq_casa, eq_fora, golos_casa, golos_fora);
            insere_fim_jogo(lst_jogos, novo_jogo);
            insere_jogo_hash(hash_table_jogos, novo_jogo);
        }
    }
}

void adiciona_equipa(int cont_linhas, int* cont_equipas, lista_equipas** hash_table_equipas)
{
    char nome_equipa[MAX];
    scanf(" %[^:\n]", nome_equipa);
    if (procura_equipa_hash(nome_equipa, hash_table_equipas) != NULL)
        printf("%d Equipa existente.\n", cont_linhas);
    else
    {
        equipa nova_equipa = cria_equipa(nome_equipa);
        (*cont_equipas)++;
        insere_equipa_hash(hash_table_equipas, nova_equipa);
    }
}

void listar_jogos(int cont_linhas, lista_jogos* lst_jogos)
{
    node_jogo* aux = lst_jogos -> inicio;
    while (aux)
    {
        printf("%d %s %s %s %d %d\n", cont_linhas, aux -> jogo -> nome, aux  -> jogo -> eq_casa -> nome, aux -> jogo -> eq_fora -> nome, aux -> jogo -> golos_casa, aux -> jogo -> golos_fora);
        aux = aux -> prox;
    }
}


void procura_jogo(int cont_linhas, lista_jogos** hash_table_jogos)
{
    char nome_jogo[MAX];
    jogo* jogo;
    scanf(" %s", nome_jogo);
    if ((jogo = procura_jogo_hash(nome_jogo, hash_table_jogos)))
        printf("%d %s %s %s %d %d\n", cont_linhas, jogo -> nome, jogo -> eq_casa -> nome, jogo -> eq_fora -> nome, jogo -> golos_casa, jogo -> golos_fora);
    else
        printf("%d Jogo inexistente.\n", cont_linhas);
}

void procura_equipa(int cont_linhas, lista_equipas** hash_table_equipas)
{
    char nome_equipa[MAX];
    equipa* equipa;
    scanf(" %s", nome_equipa);
    if ((equipa = procura_equipa_hash(nome_equipa, hash_table_equipas)))
        printf("%d %s %d\n", cont_linhas, equipa -> nome, equipa -> vitorias);
    else
        printf("%d Equipa inexistente.\n", cont_linhas);
}

void apaga_jogo(int cont_linhas, lista_jogos** hash_table_jogos)
{
    char nome[MAX];
    int hash_nome, apagado = 0;
    node_jogo* aux;
    scanf(" %s", nome);
    hash_nome = hash(nome, HASH);
    aux = hash_table_jogos[hash_nome] -> inicio;
    while (aux)
    {
        if (!strcmp(aux -> jogo -> nome, nome))
        {
            if (!aux -> ant)
            {
                hash_table_jogos[hash_nome] -> inicio = hash_table_jogos[hash_nome] -> inicio -> prox;
            }
            else if (!aux -> prox)
            {
                hash_table_jogos[hash_nome] -> fim = hash_table_jogos[hash_nome] -> fim -> ant;
            }
            else
            {
                aux -> ant -> prox = aux -> prox;
                aux -> prox -> ant = aux -> ant;
            }
            free(aux);
            apagado = 1;
        }
        aux = aux -> prox;
    }
    if(!apagado)
        printf("%d Jogo inexistente.\n", cont_linhas);
}

void altera_score(int cont_linhas, lista_jogos** hash_table_jogos)
{
    char nome[MAX];
    jogo* jogo;
    scanf(" %[^:\n]", nome);
    if (!(jogo = procura_jogo_hash(nome, hash_table_jogos)))
        printf("%d Jogo inexistente.\n", cont_linhas);
    else
    {
        repor_score(jogo -> eq_casa, jogo -> eq_fora, jogo -> golos_casa, jogo -> golos_fora);
        scanf(":%d:%d", &jogo -> golos_casa, &jogo -> golos_fora);
        atribui_vitoria(jogo -> eq_casa, jogo -> eq_fora, jogo -> golos_casa, jogo -> golos_fora);
    } 
}

void encontra_melhores_equipas(int cont_linhas, int* cont_equipas, lista_equipas** hash_table_equipas)
{
    int max = -1, num_max = 0, i, j = 0;
    char** melhores_equipas;
    if (*cont_equipas)
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
                    melhores_equipas[j++] = aux -> equipa.nome;
                } 
                aux = aux -> prox;
            }
        }
        qsort(melhores_equipas, num_max, sizeof(char*), comparador);
        printf("%d Melhores %d\n", cont_linhas, max);
        for (i = 0; i < j; i++)
        {
            printf("%d * %s\n", cont_linhas, melhores_equipas[i]);
        }
        free(melhores_equipas);
    }
}

int main()
{
    lista_jogos** hash_table_jogos = (lista_jogos**) malloc (sizeof(lista_jogos*)*HASH);
    lista_jogos* lst_jogos = cria_lista_jogos();
    lista_equipas** hash_table_equipas = (lista_equipas**) malloc (sizeof(lista_equipas*)*HASH);
    int cont_linhas = 0, cont_equipas = 0;
    char comm;
    cria_hash_table_jogos(hash_table_jogos, HASH);
    cria_hash_table_equipas(hash_table_equipas, HASH);
    while ((comm = getchar()) != 'x') /* Introducao do comando. */
    {
        switch (comm)
        {
            case 'a':
                adiciona_jogo(++cont_linhas, hash_table_equipas, lst_jogos, hash_table_jogos);
                break;
            case 'A':
                adiciona_equipa(++cont_linhas, &cont_equipas, hash_table_equipas);
                break;
            case 'l':
                listar_jogos(++cont_linhas, lst_jogos);
                break;
            case 'p':
                procura_jogo(++cont_linhas, hash_table_jogos);
                break;
            case 'P':
                procura_equipa(++cont_linhas, hash_table_equipas);
                break;
            case 'r':
                apaga_jogo(++cont_linhas, hash_table_jogos);
                break;
            case 's':
                altera_score(++cont_linhas, hash_table_jogos);
                break;
            case 'g':
                encontra_melhores_equipas(++cont_linhas, &cont_equipas, hash_table_equipas);
                break;
        }
    }
    destroi_hash_table_equipas(hash_table_equipas, HASH);
    free(hash_table_equipas);
    destroi_hash_table_jogos(hash_table_jogos, HASH);
    free(hash_table_jogos);
    destroi_lista_jogos(0, lst_jogos);
    return 0;
}
