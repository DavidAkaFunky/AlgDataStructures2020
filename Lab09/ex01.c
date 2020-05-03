#include <stdio.h>
#include <stdlib.h>

typedef struct stru_node 
{
    struct stru_node *next;
    int v;
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

/* add integer e as the first element of the list and return the new head */
node * push(node * head, int e)
{
    node *next = head;
    head = malloc(sizeof(node));
    head -> next = next;
    head -> v = e;
    return head;
}

/* frees all memory associated with the list and returns NULL */
node * destroy(node * head)
{
    while (head)
        head = pop (head);
    return NULL;
}

/* print the elements of the integers in the list, one per line */
void print(node * head)
{
    for (; head; head = head -> next)
        printf ("%d\n", head -> v);
}

int main()
{
    int v;
    node *list = NULL;
    while (1)
    {
        scanf("%d", &v);
        if (v == 0)
            break;
        list = push(list, v);
    }
    print(list);
    list = destroy(list);
    return 0;
}