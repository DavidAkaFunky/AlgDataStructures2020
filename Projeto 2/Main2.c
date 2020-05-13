#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Equipas.h"
#include "Jogos.h"
#include "Hash.h"

int cont_linha = 0, cont_equipas = 0;

void adiciona_jogo(lista_equipas** hash_table_equipas, lista_jogos* lst_jogos, lista_jogos** hash_table_jogos)
{
    char nome_jogo[MAX], nome_casa[MAX], nome_fora[MAX];
    int golos_casa, golos_fora;
    equipa *eq_casa, *eq_fora;
    cont_linha++;
    scanf(" %[^:\n]", nome_jogo);
    if (procura_jogo_hash(nome_jogo, hash_table_jogos))
        printf("%d Jogo existente.\n", cont_linha);
    else
    {
        scanf(":%[^:\n]:%[^:\n]", nome_casa, nome_fora);
        if (!((eq_casa = procura_equipa_hash(nome_casa, hash_table_equipas)) && (eq_fora = procura_equipa_hash(nome_fora, hash_table_equipas))))
            printf("%d Equipa inexistente.\n", cont_linha);
        else
        {
            jogo* novo_jogo;
            scanf(":%d:%d", &golos_casa, &golos_fora);
            novo_jogo = cria_jogo(nome_jogo, eq_casa, eq_fora, golos_casa, golos_fora);
            insere_fim_jogo(lst_jogos, novo_jogo);
            insere_jogo_hash(hash_table_jogos, novo_jogo);
        }
    }
}

void adiciona_equipa(lista_equipas** hash_table_equipas)
{
    char nome_equipa[MAX];
    cont_linha++;
    scanf(" %[^:\n]", nome_equipa);
    if (procura_equipa_hash(nome_equipa, hash_table_equipas))
        printf("%d Equipa existente.\n", cont_linha);
    else
    {
        equipa nova_equipa = cria_equipa(nome_equipa);
        cont_equipas++;
        insere_equipa_hash(hash_table_equipas, nova_equipa);
    }
}

void listar_jogos(lista_jogos* lst_jogos)
{
    node_jogo* aux = lst_jogos -> inicio;
    cont_linha++;
    while (aux)
    {
        printf("%d %s %s %d %d\n", cont_linha, aux -> jogo -> eq_casa -> nome, aux -> jogo -> eq_fora -> nome, aux -> jogo -> golos_casa, aux -> jogo -> golos_fora);
        aux = aux -> prox;
    }
}

void procura_jogo(lista_jogos** hash_table_jogos)
{
    char nome_jogo[MAX];
    jogo* jogo;
    cont_linha++;
    scanf(" %s", nome_jogo);
    if ((jogo = procura_jogo_hash(nome_jogo, hash_table_jogos)))
        printf("%d %s %s %s %d %d\n", cont_linha, jogo -> nome, jogo -> eq_casa -> nome, jogo -> eq_fora -> nome, jogo -> golos_casa, jogo -> golos_fora);
    else
        printf("%d Jogo inexistente.\n", cont_linha);
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

void apaga_jogo(lista_jogos** hash_table_jogos)
{
    char nome[MAX];
    int hash_nome, apagado = 0;
    lista_jogos* aux;
    cont_linha++;
    scanf(" %s", nome);
    hash_nome = hash(nome, HASH);
    aux = hash_table_jogos[hash_nome];
    while (aux -> inicio)
    {
        if (!strcmp(aux -> inicio -> jogo -> nome, nome))
        {
            if (!aux -> inicio -> ant)
            {
                hash_table_jogos[hash_nome] -> inicio = hash_table_jogos[hash_nome] -> inicio -> prox;
            }
            else if (!aux -> inicio -> prox)
            {
                hash_table_jogos[hash_nome] -> fim = hash_table_jogos[hash_nome] -> fim -> ant;
            }
            else
            {
                aux -> inicio -> ant -> prox = aux -> inicio -> prox;
                aux -> inicio -> prox -> ant = aux -> inicio -> ant;
            }
            free(aux);
            apagado = 1;
        }
        aux -> inicio = aux -> inicio -> prox;
    }
    if(!apagado)
        printf("%d Jogo inexistente.\n", cont_linha);
}

void altera_score(lista_jogos** hash_table_jogos)
{
    char nome[MAX];
    jogo* jogo;
    cont_linha++;
    scanf(" %[^:\n]", nome);
    if (!(jogo = procura_jogo_hash(nome, hash_table_jogos)))
        printf("%d Jogo inexistente.\n", cont_linha);
    else
    {
        repor_score(jogo -> eq_casa, jogo -> eq_fora, jogo -> golos_casa, jogo -> golos_fora);
        scanf(":%d:%d", &jogo -> golos_casa, &jogo -> golos_fora);
        atribui_vitoria(jogo -> eq_casa, jogo -> eq_fora, jogo -> golos_casa, jogo -> golos_fora);
    } 
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
    lista_jogos** hash_table_jogos = (lista_jogos**) malloc (sizeof(lista_jogos*)*HASH);
    lista_equipas** hash_table_equipas = (lista_equipas**) malloc (sizeof(lista_equipas*)*HASH);
    char comm;
    lista_jogos* lst_jogos = cria_lista_jogos();
    cria_hash_table_jogos(hash_table_jogos, HASH);
    cria_hash_table_equipas(hash_table_equipas, HASH);
    while ((comm = getchar()) != 'x') /* Introducao do comando. */
    {
        switch (comm)
        {
            case 'a':
                adiciona_jogo(hash_table_equipas, lst_jogos, hash_table_jogos);
                break;
            case 'A':
                adiciona_equipa(hash_table_equipas);
                break;
            case 'l':
                listar_jogos(lst_jogos);
                break;
            case 'p':
                procura_jogo(hash_table_jogos);
                break;
            case 'P':
                procura_equipa(hash_table_equipas);
                break;
            case 'r':
                apaga_jogo(hash_table_jogos);
                break;
            case 's':
                altera_score(hash_table_jogos);
                break;
            case 'g':
                encontra_melhores_equipas(hash_table_equipas);
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