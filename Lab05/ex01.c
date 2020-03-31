#include <stdio.h>
#define ALUNOS 10
#define DISCIPLINAS 5

long score_disciplina(int disciplina, int valores[ALUNOS][DISCIPLINAS])
{
    int aluno, soma = 0;
    for (aluno = 0; aluno < ALUNOS; aluno++)
    {
        soma += valores[aluno][disciplina];
    }
    return soma;
}

long score_aluno(int aluno, int valores[ALUNOS][DISCIPLINAS])
{
    int disciplina, soma = 0;
    for (disciplina = 0; disciplina < DISCIPLINAS; disciplina++)
    {
        soma += valores[aluno][disciplina];
    }
    return soma;
}

int main()
{
    int i, n, a, d, v, valores[ALUNOS][DISCIPLINAS] = {0}, melhor_disc, melhor_aluno, val_melhor_disc, val_melhor_aluno;
    long valor;
    scanf ("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf ("%d %d %d", &a, &d, &v);
        valores[a][d] = v;
    }
    val_melhor_aluno = -1-100 * d;
    val_melhor_disc = -1-100 * a;
    for (d = 0; d < DISCIPLINAS; d++)
    {
        if ((valor = score_disciplina (d, valores)) > val_melhor_disc)
        {
            val_melhor_disc = valor;
            melhor_disc = d;
        }
    }
    for (a = 0; a < ALUNOS; a++)
    {
        if ((valor = score_aluno (a, valores)) > val_melhor_aluno)
        {
            val_melhor_aluno = valor;
            melhor_aluno = a;
        }
    }
    printf ("%d\n%d", melhor_disc, melhor_aluno);
    return 0;
}