/* Ficheiro: Projeto2/Misc.c
 * Nome: David Emanuel Silva Belchior -- Instituto Superior Tecnico -- LEIC-A -- Numero 95550 
 * Descricao do ficheiro: Este ficheiro contem algumas funcoes que nao se encaixam totalmente nos
 * ficheiros anteriores, nomeadamente as funcoes de hashing, comparacao (usada no qsort)
 * e reposicao e atribuicao de vitorias as equipas que se defrontam nos jogos.
 */

#include "Misc.h"
#include "Equipas.h"

/* Devolve o valor da hash correpondente a uma string. */
int hash(char *v, int M)
{
    int h, a = 127;
    for (h = 0; *v != '\0'; v++)
    {
        h = (a*h + *v) % M;
    }
    return h;
}

/* Funcao de comparacao usada no qsort (funcao encontra_melhores_equipas, ficheiro Main.c). */
int comparador (const void * a, const void * b)
{
    const char *pa = *(const char**)a;
    const char *pb = *(const char**)b;
    return strcmp(pa, pb);
}

/* Atribui a vitoria a uma equipa (incrementando o seu numero de vitorias)
 * em funcao do resultado do jogo fornecido. */
void atribui_vitoria(equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora)
{
    if (golos_casa > golos_fora)
        eq_casa -> vitorias++;
    else if (golos_fora > golos_casa)
        eq_fora -> vitorias++;
}

/* Retira a vitoria ao vencedor de um jogo. Esta funcao e usada em situacoes
 * de alteracao de um resultado ou eliminacao do sistema de um jogo. */
void repor_score(equipa* eq_casa, equipa* eq_fora, int golos_casa, int golos_fora)
{
    if (golos_casa > golos_fora)
        eq_casa -> vitorias--;
    else if (golos_fora > golos_casa)
        eq_fora -> vitorias--;
}