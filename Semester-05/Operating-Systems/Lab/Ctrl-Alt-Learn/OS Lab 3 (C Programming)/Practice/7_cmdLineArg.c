#include<stdio.h>
#include<stdlib.h>

// Difference between argv and *argv

void exploreArgv(int argc, char *argv[]){
    printf("argc = %d\n", argc);

    // %p	Pointer address
    printf("argv = %p\n", (void *)argv);

    printf("*argv = %s\n", *argv);

    printf("argv[1] = %s\n", argv[1]);

    printf("*argv[1] = %c\n", *argv[1]);
}

int multiply(int argc, char *argv[])
{
    int a, b, result;

    if (argc != 3)
    {
        printf("Please enter two numbers");
        return 1;
    }

    // atoi() is a C library function used to convert a string (character array) into an integer (int).
    a = atoi(argv[1]);
    b = atoi(argv[2]);

    result = a * b;

    printf("Multiplication = %d", result);

    return 0;
}

int main(int argc, char *argv[]){

    exploreArgv(argc,argv);

    // multiply(argc,argv)
    return 0;
}