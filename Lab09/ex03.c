#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

typedef struct stru_node
{
    struct stru_node *next;
    char* v;
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
node * push(node * head, char* buffer)
{
    node *next = head;
    head = malloc(sizeof(node));
    head -> next = next;
    head -> v = (char*) malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(head -> v, buffer);
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
        printf ("%s\n", head -> v);
}

int main()
{
    char buffer[MAX];
    node *list = NULL;
    scanf("%s", buffer);
    while(strcmp(buffer, "x"))
    {
        list = push(list, buffer);
        scanf("%s", buffer);
    }
    print(list);
    list = destroy(list);
    return 0;
}