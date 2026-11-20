// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>
// #include<sys/wait.h>

// int main(){

//     int p1[2], p2[2] //child 1 p1 = write   
//     ,p3[2],p4[2]; // child 2 p3 = write 

//     int marks[8] = {65, 80, 75, 90, 55, 85, 70, 95};

//     int sum = 0 ;
//     float average = 0.0;


//     if (pipe(p1) == -1 || pipe(p2) == -1 ||
//         pipe(p3) == -1 || pipe(p4) == -1) {
//         printf("Pipe creation failed\n");
//         return 1;
//     }

//     pid_t pid1 = fork();

//     if (pid1 == 0)
//     {
//         close(p1[0]);
//         close(p2[1]);

//         close(p3[0]);
//         close(p3[1]);
//         close(p4[0]);
//         close(p4[1]);

//         int data[4];

//         read(p2[0],data,sizeof(data));

//         for(int i = 0 ; i < 4 ; i++){
//             sum += data[i];
//         }

//         write(p1[1],sum, sizeof(sum));

//         close(p1[1]);
//         close(p2[0]);

//         exit(0);
//     }

//     pid_t pid2 = fork();

//     if (pid2 == 0)
//     {
//         close(p3[0]);
//         close(p4[1]);

//         close(p1[0]);
//         close(p1[1]);
//         close(p2[0]);
//         close(p2[1]);

//         int data[4];

//         read(p4[0],data,sizeof(data));

//         int total = 0;

//         for(int i = 0 ; i < 4 ; i++){
//             total += data[i];
//         }

//         average = total / 4;
//         write(p3[1],&average, 4 * sizeof(data));

//         close(p3[1]);
//         close(p4[0]);

//         exit(0);
//     }

//     close(p1[0]);
//     close(p1[1]);
//     close(p2[0]);
//     close(p2[1]);


//     write()

    
// }

