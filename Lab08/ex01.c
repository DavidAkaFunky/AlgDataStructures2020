#include <stdio.h>
#define MAX 1000

int main()
{
    int i;
    char *p, str[MAX];
    scanf("%s", str);
    p = str;
    for (i = 0; str[i] != '\0'; i++)
    {
        printf("%s\n", p+i);
    }
    return 0;
}