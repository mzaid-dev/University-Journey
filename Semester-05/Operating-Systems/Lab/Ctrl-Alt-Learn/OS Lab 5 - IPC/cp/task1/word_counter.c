
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int total_words = argc - 1;
    int longest = 0;

    for (int i = 1; i < argc; i++) {
        int length = strlen(argv[i]);

        if (length > longest) {
            longest = length;
        }
    }

    printf("PID: %d\n", getpid());
    printf("Total words: %d\n", total_words);
    printf("Longest word length: %d\n", longest);

    return 0;
}
