//fibonacci by recurssion
#include <stdio.h>
int fibonacci(int n)
{
    if (n == 0)
        return 0;

    if (n == 1 || n == 2)
        return 1;
    else
        return (fibonacci(n - 1) + fibonacci(n - 2));
}

int main()
{
    
    int n = 10;
    printf("Fibonacci series:  ", n);

    for (int i = 0; i < n; i++) {
        printf("%d ", fibonacci(i));
    }
    return 0;
}