
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int marks[8] = {65, 80, 75, 90, 55, 85, 70, 95};

    int p1[2], p2[2];  // Child 1: input and output
    int p3[2], p4[2];  // Child 2: input and output

    int sum = 0;
    float average = 0;

    // Create four pipes
    if (pipe(p1) == -1 || pipe(p2) == -1 ||
        pipe(p3) == -1 || pipe(p4) == -1) {
        printf("Pipe creation failed\n");
        return 1;
    }

    // Create Child 1
    pid_t pid1 = fork();

    if (pid1 < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid1 == 0) {

        // Child 1

        close(p1[1]); // Close unused write end
        close(p2[0]); // Close unused read end

        // Close Child 2 pipes
        close(p3[0]);
        close(p3[1]);
        close(p4[0]);
        close(p4[1]);

        int received[4];

        // Receive first four marks
        read(p1[0], received, sizeof(received));

        // Calculate sum
        for (int i = 0; i < 4; i++) {
            sum += received[i];
        }

        // Send sum to parent
        write(p2[1], &sum, sizeof(sum));

        close(p1[0]);
        close(p2[1]);

        exit(0);
    }

    // Only original parent reaches here

    // Create Child 2
    pid_t pid2 = fork();

    if (pid2 < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid2 == 0) {

        // Child 2

        close(p3[1]); // Close unused write end
        close(p4[0]); // Close unused read end

        // Close Child 1 pipes
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        int received[4];
        int total = 0;

        // Receive last four marks
        read(p3[0], received, sizeof(received));

        // Calculate average
        for (int i = 0; i < 4; i++) {
            total += received[i];
        }

        average = total / 4.0;

        // Send average to parent
        write(p4[1], &average, sizeof(average));

        close(p3[0]);
        close(p4[1]);

        exit(0);
    }

    // Original Parent

    // Close unused pipe ends
    close(p1[0]);
    close(p2[1]);
    close(p3[0]);
    close(p4[1]);

    // Send first four marks to Child 1
    write(p1[1], marks, 4 * sizeof(int));

    // Send last four marks to Child 2
    write(p3[1], marks + 4, 4 * sizeof(int));

    // Receive sum from Child 1
    read(p2[0], &sum, sizeof(sum));

    // Receive average from Child 2
    read(p4[0], &average, sizeof(average));

    // Close remaining pipe ends
    close(p1[1]);
    close(p2[0]);
    close(p3[1]);
    close(p4[0]);

    // Wait for both children
    wait(NULL);
    wait(NULL);

    // Display results
    printf("\nChild 1 - Sum of first four marks: %d\n", sum);

    printf("Child 2 - Average of last four marks: %.2f\n", average);

    printf("Parent: Both child processes completed.\n");

    return 0;
}
