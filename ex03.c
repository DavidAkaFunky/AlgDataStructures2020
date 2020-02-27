#include <stdio.h>

int main()
{
    int n, i, div = 2;
    scanf ("%d", &n);
    for (i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            div++;
    }
    printf("%d\n", div);
    return 0;
}