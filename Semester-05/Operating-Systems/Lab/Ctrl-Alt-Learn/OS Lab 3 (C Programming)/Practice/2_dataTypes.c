#include<stdio.h>


int main(){
    int age = 20;
    float marks = 30.2;
    char grade = 'A';

    // Why %?
    // In quotes ("%d"), % marks a data type placeholder for printf()/scanf(). In math (10 % 3), % returns the remainder after division.

    printf("Age : %d\n",age);
    printf("Marks : %f\n",marks);
    printf("Age : %c\n",grade);

}