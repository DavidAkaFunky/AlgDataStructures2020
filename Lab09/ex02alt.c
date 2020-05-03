#include <stdio.h>
#include <stdlib.h>
typedef struct stru_node {
    struct stru_node *next;
    int v;
} node;
/* remove the first element of the list and return the new head */
node * pop(node * head) {
    node *next;
    if(head == NULL) return NULL;
    next = head->next;
    free(head);
    return next;
}
/* add integer e as the first element of the list and return the new head */
node * push(node * head, int e) {
    node *old = head;
    head = malloc(sizeof(node));
    head->next = old;
    head->v = e;
    return head;
}
/* frees all memory associated with the list and returns NULL */
node * destroy(node * head) {
    while (head) {
       head = pop(head);
    }
    return NULL;
}
/* print the elements of the integers in the list, one per line */
void print(node * head) {
    for(; head; head = head->next) {
        printf("%d\n", head->v);
    }
}
/* compara duas listas */
int is_eq(node *h1, node *h2) {
    while(1) {
        if(!h1 && !h2) return 1;
        if((!h1 && h2) || (h1 && !h2)) return 0;
        if(h1-> v != h2-> v) return 0;
        h1 = h1->next;
        h2 = h2->next;
    }
    return 0;
}
/* devolve uma nova lista que corresponda a lista dada invertida */
node * rev(node * head) {
    node *new = NULL;
    for(; head; head = head->next) {
        new = push(new, head->v);
    }
    return new;
}
int main() {
    int v;
    node *list_r = NULL, *list = NULL;
    while ((v = getchar()) != EOF && v != '\n') {
        list = push(list, v);
    }
    list_r = rev(list);
    puts(is_eq(list, list_r) ? "yes": "no");
    destroy(list);
    destroy(list_r);
    return 0;
}