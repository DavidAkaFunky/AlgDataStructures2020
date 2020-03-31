#include <stdio.h>
#define IN 1
#define OUT 0

int main ()
{
    int modo = OUT;
    char c, ant = ' ';
    while ((c = getchar()) != EOF)
    {
        if ('1' <= c && c <= '9')
        {
            putchar (c);
            modo = IN;
        }
        else if (c == '\n' || c == '\t' || c == ' ')
        {
            if (modo == OUT && ant == '0')
            {
                putchar (ant);
            }
            putchar (c);
            modo = OUT;
        }
        else if (c == '0' && modo == IN)
        {
            putchar (c);
        }
        ant = c;
    }
    if (modo == OUT && ant == '0')
    {
        putchar (ant);
    }
    return 0;
}