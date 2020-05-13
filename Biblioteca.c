#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char* nome;
    char* autor;
    int ano;
    char* tema;
} Livro;

typedef struct stru_node
{
    Livro* livro;
    struct stru_node *next;
} node;

/* remove the first element of the list and return the new head */
node * pop(node * head)
{
    node *next;
    if (head == NULL)
        return NULL;
    next = head -> next;
    free (head);
    return next;
}

/* add buffer as the first element of the list and return the new head*/
node * push(node * head, Livro* livro_novo)
{
    node *next = head;
    head = malloc(sizeof(node));
    head -> next = next;
    head -> livro = (Livro*) malloc(sizeof(Livro));
    strcpy(head -> livro -> nome, livro_novo -> nome);
    strcpy(head -> livro -> autor, livro_novo -> autor);
    livro_novo -> ano = head -> livro -> ano;
    strcpy(head -> livro -> tema, livro_novo -> tema);
    return head;
}

/* frees all memory associated with the list and returns NULL */
node * destroy(node * head)
{
    while (head)
        head = pop(head);
    return NULL;
}

/* print the elements of the strings in the list, one per line */
void print(node * head)
{
    for (; head; head = head -> next)
        printf ("%s, %s, %d, %s\n", head -> livro -> nome, head -> livro -> autor, head -> livro -> ano, head -> livro -> tema);
}

node* carrega_livros(node* biblioteca)
{
    int contador = 0;
    FILE* dados;
    char linha[10000];
    Livro* livro_novo = NULL;
    puts("Gestor de biblioteca\nFeito por David Belchior\nmaio 2020\nA carregar...");
    dados = fopen("Biblioteca.txt", "a+");
    memset(linha, '\0', sizeof(linha));
    if (dados == NULL)
    {
        puts("Nao existem dados :/");
        exit(EXIT_FAILURE);
    }
    while (fgets(linha, sizeof(linha), dados))
    {
        sscanf(linha, "%s, %s, %d, %s", livro_novo -> nome, livro_novo -> autor, &(livro_novo -> ano), livro_novo -> tema);
        biblioteca = push(biblioteca, livro_novo);
        contador++;
    }
    puts("Concluido!");
    return biblioteca;
}

int main()
{
    node* biblioteca = NULL;
    biblioteca = carrega_livros(biblioteca);
    print(biblioteca);
    destroy(biblioteca);
    /*while ((comm = getchar()) != 'x') Introducao do comando.
    {
        switch (comm)
        {
            case 'a':

        }
    }*/
    return 0;
}