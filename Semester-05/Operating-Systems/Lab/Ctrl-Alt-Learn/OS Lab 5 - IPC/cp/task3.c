
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: ./threshold threshold values...\n");
        return 1;
    }

    double threshold = atof(argv[1]);

    int n = argc - 2;
    double values[n];

    for (int i = 0; i < n; i++) {
        values[i] = atof(argv[i + 2]);
    }

    int p1[2], p2[2];

    pipe(p1);
    pipe(p2);

    int size1 = n / 2;
    int size2 = n - size1;

    pid_t pid1 = fork();

    if (pid1 == 0) {
        close(p1[0]);
        close(p2[0]);
        close(p2[1]);

        int count = 0;

        for (int i = 0; i < size1; i++) {
            if (values[i] > threshold) {
                count++;
            }
        }

        write(p1[1], &count, sizeof(count));

        printf("Child 1 Count: %d\n", count);

        close(p1[1]);
        exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        close(p2[0]);
        close(p1[0]);
        close(p1[1]);

        int count = 0;

        for (int i = size1; i < n; i++) {
            if (values[i] > threshold) {
                count++;
            }
        }

        write(p2[1], &count, sizeof(count));

        printf("Child 2 Count: %d\n", count);

        close(p2[1]);
        exit(0);
    }

    close(p1[1]);
    close(p2[1]);

    int count1, count2;

    read(p1[0], &count1, sizeof(count1));
    read(p2[0], &count2, sizeof(count2));

    int total = count1 + count2;

    printf("\nParent PID: %d\n", getpid());
    printf("Total matching values: %d\n", total);

    if (count1 > count2) {
        printf("Child 1 processed more matches.\n");
    }
    else if (count2 > count1) {
        printf("Child 2 processed more matches.\n");
    }
    else {
        printf("Both children processed equal matches.\n");
    }

    close(p1[0]);
    close(p2[0]);

    wait(NULL);
    wait(NULL);

    return 0;
}
