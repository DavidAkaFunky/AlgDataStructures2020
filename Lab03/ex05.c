#include <stdio.h>
#define IN 1
#define OUT 0

int main ()
{
    int modo = OUT, barra = OUT;
    char c;
    while ((c = getchar()) != EOF)
    {
        if (c == '\"')
        {
            modo = IN;
        }
        while (modo == IN)
        {
            if (c == '\\' && barra == OUT)
            {
                barra = IN;
            }
            else
            {
                putchar (c);
                if (c == '\"' && barra == OUT)
                {
                    modo = OUT;
                }
                if (c != '\\')
                {
                    barra = OUT;
                }
            }
        }
        putchar ('\n');
    }    
    return 0;
}