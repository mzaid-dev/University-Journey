
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t p1, p2, p3, p4, p5;

    p1 = fork();

    if(p1 == 0)
    {
        p3 = fork();

        if(p3 == 0)
        {
            p5 = fork();

            if(p5 == 0)
                printf("P5\n");
            else
                printf("P3\n");
        }
        else
        {
            p4 = fork();

            if(p4 == 0)
                printf("P4\n");
            else
                printf("P1\n");
        }
    }
    else
    {
        p2 = fork();

        if(p2 == 0)
            printf("P2\n");
        else
            printf("P0\n");
    }

    return 0;
}
