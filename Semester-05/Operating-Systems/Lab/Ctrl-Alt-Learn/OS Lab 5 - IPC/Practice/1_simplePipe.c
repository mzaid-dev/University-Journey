#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

// int main(int argc, char *argv[]){
    
//     int fd[2], total;

    

//     if (pipe(fd) == -1)
//     {
//         printf("pipe creation failed.\n");
//     }

//     pid_t pid = fork();

//     if (pid == 0)
//     {

//         close(fd[1]);
//         char recived[argc];
//         read(fd[0],recived,argc);

//         for (int i = 0; i < argc; i++)
//         {
//             printf("%s",recived[i]);
//         }
        
//     }else if (pid > 0)
//     {
//         close(fd[0]);

//         write(fd[1],argv,argc);


//     }

// }

int main(){

    int fd[2];
    char msg[] = "hello bro";

    if(pipe(fd) == -1){
        printf("pipe creation failed.\n");
        return 1;
    }

    pid_t pid = fork();


    if (pid < 0)
    {
        printf("fork creation failed.\n");
        return 1;
    }else if (pid > 0)
    {
        close(fd[0]);
        
        write(fd[1],msg,strlen(msg));

    }else{
        close(fd[1]);
        char reply[strlen(msg)];
        read(fd[0],reply,strlen(msg)-2);

        printf("msg : %s",reply);

    }
    
    
}


