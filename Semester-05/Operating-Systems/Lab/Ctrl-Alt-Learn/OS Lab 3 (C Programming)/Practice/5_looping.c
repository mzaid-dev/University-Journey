#include <stdio.h>

int main()
{
    int arr[20];
    int n = 0;
    int i, j, temp;

    printf("Enter numbers (maximum 20, -99 to stop):\n");

    while (n < 20)
    {
        scanf("%d", &arr[n]);

        if (arr[n] == -99)
        {
            break;
        }

        n++;
    }

    printf("Original sequence: ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    // Bubble Sort
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("\nSorted sequence: ");

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}