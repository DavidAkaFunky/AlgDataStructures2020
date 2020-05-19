#ifndef _EQUIPAS_H_
#define _EQUIPAS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char* nome;
    int vitorias;
} equipa;

equipa* cria_equipa(char* nome);

equipa** insere_equipa_hash(equipa** h_equipas, equipa* nova_equipa, int* cont_equipas, int* tam_h_equipas);

equipa* procura_equipa_hash(char* nome, equipa** h_equipas, int tam_h_equipas);

void destroi_h_equipas(equipa** h_equipas, int tam_h_equipas);

#endif
