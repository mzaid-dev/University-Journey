#include<stdio.h>
#include<stdlib.h>
// malloc stands for memory allocation.
// syntax
// ptr = (castType*) malloc(size);
int main (){

    int n = 5;
    int *arr;

    arr = malloc(n * sizeof(int));

    if(arr == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }
    
    for (int i = 0; i < n; i++)
    {
        printf("Enter number %d: ", i + 1);
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    printf("Array elements: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr = NULL;

    return 0;
    

}