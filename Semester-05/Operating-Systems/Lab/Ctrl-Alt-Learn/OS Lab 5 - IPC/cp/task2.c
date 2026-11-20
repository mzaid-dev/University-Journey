
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Enter numbers!\n");
        return 1;
    }

    int n = argc - 1;
    double values[n];

    for (int i = 0; i < n; i++) {
        values[i] = atof(argv[i + 1]);
    }

    int p1[2], p2[2];
    int p3[2], p4[2];

    pipe(p1);
    pipe(p2);
    pipe(p3);
    pipe(p4);

    pid_t pid1 = fork();

    if (pid1 == 0) {
        close(p1[1]);
        close(p2[0]);
        close(p3[0]);
        close(p3[1]);
        close(p4[0]);
        close(p4[1]);

        int size;
        read(p1[0], &size, sizeof(size));

        double sum = 0, value;

        for (int i = 0; i < size; i++) {
            read(p1[0], &value, sizeof(value));
            sum += value;
        }

        double avg = sum / size;
        write(p2[1], &avg, sizeof(avg));

        close(p1[0]);
        close(p2[1]);
        exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 == 0) {
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        close(p3[1]);
        close(p4[0]);

        int size;
        read(p3[0], &size, sizeof(size));

        double sum = 0, value;

        for (int i = 0; i < size; i++) {
            read(p3[0], &value, sizeof(value));
            sum += value;
        }

        double avg = sum / size;
        write(p4[1], &avg, sizeof(avg));

        close(p3[0]);
        close(p4[1]);
        exit(0);
    }

    close(p1[0]);
    close(p2[1]);
    close(p3[0]);
    close(p4[1]);

    int size1 = n / 2;
    int size2 = n - size1;

    write(p1[1], &size1, sizeof(size1));

    for (int i = 0; i < size1; i++) {
        write(p1[1], &values[i], sizeof(values[i]));
    }

    write(p3[1], &size2, sizeof(size2));

    for (int i = size1; i < n; i++) {
        write(p3[1], &values[i], sizeof(values[i]));
    }

    close(p1[1]);
    close(p3[1]);

    double avg1, avg2;

    read(p2[0], &avg1, sizeof(avg1));
    read(p4[0], &avg2, sizeof(avg2));

    double overall = (avg1 * size1 + avg2 * size2) / n;

    printf("Parent PID: %d\n", getpid());
    printf("Child 1 Average: %.2f\n", avg1);
    printf("Child 2 Average: %.2f\n", avg2);
    printf("Overall Average: %.2f\n", overall);

    close(p2[0]);
    close(p4[0]);

    wait(NULL);
    wait(NULL);

    return 0;
}
