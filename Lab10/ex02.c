#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct str_node
{
    struct str_node * next, * previous;
    char c;
} node;

typedef struct
{
    struct str_node *  head, * last;
} list;

/* cria nova lista vazia */
list* mk_list()
{
    list* new = malloc(sizeof(list));
    new -> head = new -> last = NULL;
    return new;
}

/* liberta toda a memoria associada a lista */
void  free_list(list* l)
{
    while (l -> head)
    {
        node* aux = l -> head -> next;
        free(l -> head);
        l -> head = aux;
    }
    free(l);
}

void add_last(list* l, char c)
{
    node* n = malloc(sizeof(node));
    n -> next = NULL;
    n -> previous = l -> last;
    n -> c = c;
    if (l -> last)
        l -> last -> next = n;
    l -> last = n;
    if (!l -> head)
        l -> head = n;
}

int is_paly(const list * ls)
{
    node* i = ls -> head;
    node* j = ls -> last;
    while (i != j && j -> next != i)
    {
        if (i -> c != j -> c)
            return 0;
        i = i -> next;
        j = j -> previous;
    }
    return 1;
}

int main()
{
    char c;
    list* ls = mk_list();
    while((c = getchar()) != EOF && c != '\n')
        add_last(ls, c);
    puts(is_paly(ls) ? "yes" : "no");
    free_list(ls);
    return 0;
}