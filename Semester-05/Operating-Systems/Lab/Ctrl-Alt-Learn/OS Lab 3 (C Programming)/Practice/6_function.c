#include<stdio.h>


void greet()
{
    printf("Welcome to C programming");
}

void add(int a, int b)
{
    printf("%d", a + b);
}

#include <stdio.h>

void checkPrimeNumber()
{
    int n, i, isPrime = 1;

    printf("Enter the number: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        isPrime = 0;
    }
    else
    {
        for (i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                isPrime = 0;
                break;
            }
        }
    }

    if (isPrime == 1)
    {
        printf("Prime");
    }
    else
    {
        printf("Not Prime");
    }
}

int main()
{
    greet();

    add(5, 3);

    checkPrimeNumber();

    return 0;
}