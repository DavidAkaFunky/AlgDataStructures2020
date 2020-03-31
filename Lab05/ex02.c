#include <stdio.h>

typedef struct
{
    float real;
    float imag;
} complexo;

complexo ler_complexo ()
{
    complexo a;
    char sinal, i;
    scanf ("%f%c%f%c", &a.real, &sinal, &a.imag, &i);
    if (sinal == '-')
    {
        a.imag = -a.imag;
    }
    return a;
}

complexo soma_complexos (complexo a, complexo b)
{
    complexo res;
    res.real = a.real + b.real;
    res.imag = a.imag + b.imag;
    return res;
}

void escrever_complexo (complexo a)
{
    if (a.imag == 0)
    {
        printf ("%.2f", a.real);
    }
    else if (a.imag < 0)
    {
        printf ("%.2f%.2fi", a.real, a.imag);
    }
    else
    {
        printf ("%.2f+%.2fi", a.real, a.imag);
    }
    
}

int main()
{
    complexo a = ler_complexo (), b = ler_complexo (), res = soma_complexos (a,b);
    escrever_complexo(res);
    return 0;
}