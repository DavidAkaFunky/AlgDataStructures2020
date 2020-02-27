#include <stdio.h>

int main()
{
    int N, soma = 0, i = 0;
    scanf ("%d", &N);
    while (N != 0)
    {
        i ++;
        soma += N % 10;
        N = N / 10;
    }
    printf("%d\n%d\n", i, soma);
    return 0;
}