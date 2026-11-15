#include<stdio.h>

// Why &age?

// & gives the memory address of the variable. scanf() needs that address so it knows where to store the entered value.
int main(){
    int age;

    printf("enter you age :");
    scanf("%d",&age);
    printf("Your age is %d", age);
    
    return 0;

}
