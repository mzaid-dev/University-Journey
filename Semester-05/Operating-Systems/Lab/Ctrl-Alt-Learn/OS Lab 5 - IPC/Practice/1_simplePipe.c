#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[]){
    
    int fd[2];

    

    if (pipe(fd) == -1)
    {
        printf("pipe creation failed.\n");
    }

    pid_t pid = fork();

    if (pid == 0)
    {

        close(fd[1]);
        char recived[argc];
        read(fd[0],recived,argc);

        for (int i = 0; i < argc; i++)
        {
            printf("%s",recived[i]);
        }
        
    }else if (pid > 0)
    {
        close(fd[0]);

        write(fd[1],argv,argc);


    }
    
    


}