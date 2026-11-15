#include <stdio.h>

int main()
{
    int a, b, c;

    printf("Enter three sides: ");
    scanf("%d %d %d", &a, &b, &c);

    if (a <= 0 || b <= 0 || c <= 0)
    {
        printf("Invalid triangle");
    }
    else if (a + b > c && a + c > b && b + c > a)
    {
        if (a == b && b == c)
        {
            printf("Equilateral triangle");
        }
        else if (a == b || a == c || b == c)
        {
            printf("Isosceles triangle");
        }
        else
        {
            printf("Scalene triangle");
        }
    }
    else
    {
        printf("Invalid triangle");
    }

    return 0;
}


// switch (choice)
// {
//     case 1:
//         printf("One");
//         break;

//     case 2:
//         printf("Two");
//         break;

//     default:
//         printf("Invalid choice");
// }