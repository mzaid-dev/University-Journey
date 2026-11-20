
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: ./launcher word1 word2 ...\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        execv("./word_counter", argv);
        perror("execv");
    }
    else if (pid > 0) {
        int status;
        wait(&status);

        printf("Child process finished.\n");
    }
    else {
        perror("fork");
    }

    return 0;
}
