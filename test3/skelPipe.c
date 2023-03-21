#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>

int checkCall(int val, char *str)
{
    if (val == -1)
    {
        if (val == EINTR) return val;
        perror(str);
        exit(EXIT_FAILURE);
    }
    return val;
}

void producer(int fd[2]) // Takes an array found in the pipe as an argument.
{

    char wor[120];
    // Close the read side of the pipe
    close(fd[0]);

    dup(fd[1]);

    char *exp[] = {"cat", "filename.txt", NULL};
    if( (execvp("cat", exp)) < 0) {
      perror("Execvp failed from child");
       exit(EXIT_FAILURE);
    }
    checkCall(write(fd[1], &wor, sizeof(wor)),"write into the pipe"); // Write the word onto the pipe.
    close(fd[1]); // When done, close that side of the pipe.
    exit(EXIT_SUCCESS);

}

void consumer(int fd[2])
{
    char wor[120];


    // Close the write side of the pipe
    close(fd[1]);
    checkCall(read(fd[0], &wor, sizeof(wor)),"read from the pipe");
    printf("Parent: %s\n", wor); // Parent will output the sum it computed
    close(fd[0]); // When done, close that side of the pipe.
    exit(EXIT_SUCCESS);
}

int main(int argc, char*argv[])
{
    int fd[2];
    pid_t cPid;
    checkCall(pipe(fd), "pipe");

    cPid = checkCall(fork(), "fork");
     switch (cPid)
     {
         /* do something in child */
         case 0:
             producer(fd); // In the child, we call the producer.
             break;

         /* do something in parent */
         default:
             consumer(fd); // In the parent, we call the consumer.
             break;
     }


    return 0;
}
