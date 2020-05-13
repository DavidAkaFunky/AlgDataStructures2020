#include "Jogos.h"
#include "Equipas.h"
#include "Hash.h"

lista_jogos* cria_lista_jogos()
{
    lista_jogos* novo = malloc(sizeof(lista_jogos));
    novo -> inicio = novo -> fim = NULL;
    return novo;
}

void atribui_vitoria(equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora)
{
    if (golos_casa > golos_fora)
        eq_casa -> vitorias++;
    else if (golos_fora > golos_casa)
        eq_fora -> vitorias++;
}
    
void repor_score(equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora)
{
    if (golos_casa > golos_fora)
        eq_casa -> vitorias--;
    else if (golos_fora > golos_casa)
        eq_fora -> vitorias--;
}

jogo* cria_jogo(char* nome, equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora)
{
    jogo* novo_jogo = (jogo*) malloc(sizeof(jogo));
    novo_jogo -> nome = (char*) malloc (strlen(nome)+1);
    strcpy(novo_jogo -> nome, nome);
    novo_jogo -> eq_casa = eq_casa;
    novo_jogo -> eq_fora = eq_fora;
    novo_jogo -> golos_casa = golos_casa;
    novo_jogo -> golos_fora = golos_fora;
    atribui_vitoria(eq_casa, eq_fora, golos_casa, golos_fora);
    return novo_jogo;
}

void insere_fim_jogo(lista_jogos* l, jogo* novo_jogo)
{
    node_jogo* n = malloc(sizeof(node_jogo));
    n -> prox = NULL;
    n -> ant = l -> fim;
    n -> jogo = novo_jogo;
    if (l -> fim)
        l -> fim -> prox = n;
    l -> fim = n;
    if (!l -> inicio)
        l -> inicio = n;
}

jogo* procura_jogo_hash(char* nome, lista_jogos** hash_table_jogos)
{
    int hash_nome = hash(nome, HASH);
    lista_jogos* aux = hash_table_jogos[hash_nome];
    while (aux -> inicio)
    {
        if (!strcmp(aux -> inicio -> jogo -> nome, nome))
        {
            return aux -> inicio -> jogo;
        }
        aux -> inicio = aux -> inicio -> prox;
    }
    return NULL;
}

void destroi_lista_jogos(lista_jogos* l)
{
    while (l -> inicio)
    {
        node_jogo* aux = l -> inicio -> prox;
        if(l-> inicio -> jogo)
        {
            if (l -> inicio -> jogo -> eq_casa && l -> inicio -> jogo -> eq_fora)
            {
                free (l -> inicio -> jogo -> eq_casa);
                free (l -> inicio -> jogo -> eq_fora);
            }
            free (l -> inicio -> jogo);
        }
        free(l -> inicio);
        l -> inicio = aux;
    }
    free(l);
}

void cria_hash_table_jogos(lista_jogos** hash_table_jogos, int hash)
{
    int i;
    for (i = 0; i < hash; i++)
    {
        hash_table_jogos[i] = cria_lista_jogos();
    }
}

void insere_jogo_hash(lista_jogos** hash_table_jogos, jogo* novo_jogo)
{
    int hash_nome = hash(novo_jogo -> nome, HASH);
    insere_fim_jogo(hash_table_jogos[hash_nome], novo_jogo);
}

void destroi_hash_table_jogos(lista_jogos** hash_table_jogos, int hash)
{
    int i;
    for (i = 0; i < hash; i++)
    {
        destroi_lista_jogos(hash_table_jogos[i]);
    }
}