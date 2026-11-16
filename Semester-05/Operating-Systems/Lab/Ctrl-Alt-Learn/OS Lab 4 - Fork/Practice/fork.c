// #include<stdio.h>
// #include<unistd.h>

// int main(){

//     pid_t fork_ = fork();


//     if(fork_ < 0){
//         printf("fork creation failed.\n");
//         return 1;
//     }else if (fork_ == 0)
//     {
//         printf("child created.\n");
//     }else{
//         printf("parent created.\n");
//     }

// }


// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     pid_t pid = fork();

//     if (pid == 0)
//     {
//         printf("Child PID: %d\n", getpid());
//         printf("Parent PID: %d\n", getppid());
//     }
//     else if (pid > 0)
//     {
//         printf("Parent PID: %d\n", getpid());
//         printf("Child PID: %d\n", pid);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>


// #include <stdio.h>      // printf()
// #include <unistd.h>    // fork(), getpid(), sleep(), exec()
// #include <sys/wait.h>  // wait(), waitpid()
// #include <stdlib.h>    // exit()


// int main()
// {
//     pid_t pid = fork();

//     if (pid < 0)
//     {
//         printf("Fork failed!\n");
//         return 1;
//     }

//     if (pid == 0)
//     {
//         printf("Child Process. PID: %d\n", getpid());
//         exit(0);
//     }
//     else
//     {
//         printf("Waiting for child to finish proccess.\n");
//         wait(NULL);
//         printf("Parent Process. PID: %d\n", getpid());
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

// int main()
// {
//     pid_t pid;

//     printf("Original PID: %d\n", getpid());

//     pid = fork();

//     if (pid > 0)
//     {
//         printf("Parent PID: %d\n", getpid());
//         printf("Child PID: %d\n", pid);
//         printf("Parent terminating.\n");
//     }
//     else if (pid == 0)
//     {
//         sleep(10);

//         printf("Child PID: %d\n", getpid());
//         printf("Child PPID: %d\n", getppid());

//         exit(0);
//     }

//     return 0;
// }


// #include <stdio.h>
// #include <unistd.h>

// int main()
// {
//     fork();
//     fork();
//     fork();

//     printf("Hello fork...\n");

//     return 0;
// }


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

// int main()
// {
//     pid_t pid = fork();

//     if (pid < 0)
//     {
//         printf("Fork failed!\n");
//         return 1;
//     }

//     else if (pid == 0)
//     {
//         printf("Child Process PID: %d\n", getpid());

//         for (char ch = 'A'; ch <= 'E'; ch++)
//         {
//             printf("Child: %c\n", ch);
//             sleep(1);
//         }
//     }

//     else
//     {
//         printf("Parent Process PID: %d\n", getpid());

//         for (int i = 1; i <= 5; i++)
//         {
//             printf("Parent: %d\n", i);
//             sleep(1);
//         }

//         wait(NULL);

//         printf("Parent: Child process completed.\n");
//     }

//     return 0;
// }

// int main(){
//     pid_t pid = fork();


//     if (pid == 0)
//     {
//         execlp("date","date",NULL);
//     }else
//     {
//         printf("parent : wait for child working.\n");

//         wait(NULL);

//         printf("parent procees completed.\n");

//     }
    
    
// }



