#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARS 1000
#define MAX_PALS 10000

int main()
{
    int i;
    char *lista[MAX_PALS], buffer[MAX_CHARS];
    for (i = 0; scanf("%s", buffer) > 0; i++)
    {
        lista[i] = (char *) malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(lista[i], buffer);
    }
    for (i--; i >= 0; i--)
        printf("%s\n", lista[i]);
    return 0;
}