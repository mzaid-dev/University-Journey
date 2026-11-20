
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    int p1[2], p2[2], p3[2];
    int p4[2], p5[2], p6[2];

    int number = 10;

    // Create six pipes
    pipe(p1); // Parent -> Child 1
    pipe(p2); // Child 1 -> Child 2
    pipe(p3); // Child 2 -> Child 3
    pipe(p4); // Child 3 -> Child 2
    pipe(p5); // Child 2 -> Child 1
    pipe(p6); // Child 1 -> Parent

    pid_t c1 = fork();

    if (c1 == 0) {

        // Child 1 creates Child 2
        pid_t c2 = fork();

        if (c2 == 0) {

            // Child 2 creates Child 3
            pid_t c3 = fork();

            if (c3 == 0) {

                // CHILD 3

                close(p1[0]); close(p1[1]);
                close(p2[0]); close(p2[1]);
                close(p3[1]);
                close(p4[0]);
                close(p5[0]); close(p5[1]);
                close(p6[0]); close(p6[1]);

                read(p3[0], &number, sizeof(number));

                number = number + 2;

                printf("Child 3: %d\n", number);

                write(p4[1], &number, sizeof(number));

                close(p3[0]);
                close(p4[1]);

                exit(0);
            }

            // CHILD 2

            close(p1[0]); close(p1[1]);
            close(p2[1]);
            close(p3[0]);
            close(p4[1]);
            close(p5[0]);
            close(p6[0]); close(p6[1]);

            // Forward communication
            read(p2[0], &number, sizeof(number));

            number = number + 1;

            printf("Child 2 forward: %d\n", number);

            write(p3[1], &number, sizeof(number));

            close(p2[0]);
            close(p3[1]);

            wait(NULL);

            // Reverse communication
            read(p4[0], &number, sizeof(number));

            number = number + 2;

            printf("Child 2 reverse: %d\n", number);

            write(p5[1], &number, sizeof(number));

            close(p4[0]);
            close(p5[1]);

            exit(0);
        }

        // CHILD 1

        close(p1[1]);
        close(p2[0]);
        close(p3[0]); close(p3[1]);
        close(p4[0]); close(p4[1]);
        close(p5[1]);
        close(p6[0]);

        // Forward communication
        read(p1[0], &number, sizeof(number));

        number = number + 1;

        printf("Child 1 forward: %d\n", number);

        write(p2[1], &number, sizeof(number));

        close(p1[0]);
        close(p2[1]);

        wait(NULL);

        // Reverse communication
        read(p5[0], &number, sizeof(number));

        number = number + 2;

        printf("Child 1 reverse: %d\n", number);

        write(p6[1], &number, sizeof(number));

        close(p5[0]);
        close(p6[1]);

        exit(0);
    }

    // PARENT

    close(p1[0]);
    close(p2[0]); close(p2[1]);
    close(p3[0]); close(p3[1]);
    close(p4[0]); close(p4[1]);
    close(p5[0]); close(p5[1]);
    close(p6[1]);

    // Send initial value
    write(p1[1], &number, sizeof(number));

    close(p1[1]);

    // Wait for Child 1
    wait(NULL);

    // Receive final result
    read(p6[0], &number, sizeof(number));

    printf("Parent: Final result = %d\n", number);

    close(p6[0]);

    return 0;
}
