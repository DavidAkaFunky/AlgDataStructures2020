/* Ficheiro: Projeto2/Equipas.c
 * Nome: David Emanuel Silva Belchior -- Instituto Superior Tecnico -- LEIC-A -- Numero 95550 
 * Descricao generica: Sistema de jogos amigáveis, envolvendo equipas e jogos, alem de operacoes
 * sobre estas entidades (criacao, alteracao de parametros e remocao).
 * Descricao especifica: Este ficheiro contem as funcoes usadas nas funcoes basicas sobre equipas,
 * nomeadamente de criacao de equipas e adicao, remocao de elementos e destruicao da hash table existente.
 */

#include "Equipas.h"
#include "Misc.h"

/* Inicializa uma nova equipa com nome fornecido na funcao adiciona_equipa. */
equipa* cria_equipa(char* nome)
{
    equipa* nova_equipa = (equipa*) malloc(sizeof(equipa));
    nova_equipa -> nome = (char*) malloc(strlen(nome)+1);
    strcpy(nova_equipa -> nome, nome);
    nova_equipa -> vitorias = 0;
    return nova_equipa;
}

/* FUNCOES SOBRE HASH TABLES DE EQUIPAS: Esta hash table recorre a resolução
 * linear de conflitos entre keys com o mesmo valor (linear probing). */

/* Insere uma equipa na hash table. Se o numero de equipas ultrapassar metade da hash
 * table, ela e realocada para uma nova tabela com o dobro da dimensao inicial. */
equipa** insere_equipa_hash(equipa** h_equipas, equipa* nova_equipa, int* cont_equipas, int* tam_h_equipas)
{
    int i = hash(nova_equipa -> nome, *tam_h_equipas);
    while (h_equipas[i])
        i = (i+1) % (*tam_h_equipas);
    h_equipas[i] = nova_equipa;
    if (*cont_equipas > *tam_h_equipas/2) /* Verifica se e necessaria realocacao. */
    {
        int j, novo_tam_h_equipas = 2*(*tam_h_equipas);
        equipa** aux = (equipa**) calloc (novo_tam_h_equipas, sizeof(equipa*));
        for (j = 0; j < *tam_h_equipas; j++)
            if (h_equipas[j])
                insere_equipa_hash(aux, h_equipas[j], cont_equipas, &novo_tam_h_equipas);
        free(h_equipas);
        *tam_h_equipas = novo_tam_h_equipas;
        h_equipas = aux;
    }
    return h_equipas;
}

/* Procura uma equipa na hash table, dado um nome.
 * Se ela existir, um ponteiro para essa equipa e devolvido pela funcao. */
equipa* procura_equipa_hash(char* nome, equipa** h_equipas, int tam_h_equipas)
{
    int i;
    i = hash(nome, tam_h_equipas);
    while (h_equipas[i])
    {
        if (!strcmp(h_equipas[i] -> nome, nome))
            return h_equipas[i];
        i = (i+1) % tam_h_equipas;
    }
    return NULL;
}

/* Remove todas as equipas da hash table (incluindo os seus
 * nomes) previamente alocados, e destroi a propria tabela. */
void destroi_h_equipas(equipa** h_equipas, int tam_h_equipas)
{
    int i;
    for (i = 0; i < tam_h_equipas; i++)
        if (h_equipas[i])
        {
            free(h_equipas[i] -> nome);
            free(h_equipas[i]);
        }
    free(h_equipas);
}