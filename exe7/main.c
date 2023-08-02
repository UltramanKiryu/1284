// Solving the problem we talked about in the lecture.
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

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

    char wor[60];
    // Close the read side of the pipe
    close(fd[0]);

    // User-input to be read into the pipe
    char *out = "Please enter text at the parent:\n";
    write(STDOUT_FILENO, out, 33);
    read(STDIN_FILENO,wor,40);

    checkCall(write(fd[1], &wor, sizeof(wor)),"write into the pipe"); // Write the word onto the pipe.
    close(fd[1]); // When done, close that side of the pipe.
    exit(EXIT_SUCCESS);
}

void consumer(int fd[2])
{
    char wor[60];


    // Close the write side of the pipe
    close(fd[1]);
    checkCall(read(fd[0], &wor, sizeof(wor)),"read from the pipe");
    printf("Parent: %s\n", wor); // Parent will output the sum it computed
    close(fd[0]); // When done, close that side of the pipe.
    exit(EXIT_SUCCESS);
}

// Generating a random number of values, send across the pipe, create their sum.
int main(int argc, char *argv[])
{
    // Pipes are created with pipe, so both file descriptors are opened when pipe returns successfully.
    // If try to read something from the pipe and there's nothing there, it blocks.
    // If try to write to the pipe and it's full, it blocks.
    // If it's not full, write won't block.
    // If you're only reading once or reading a small buffer, the parent may not read all the data off the pipe if it does one read.
    // Reading 1024 bytes and only 2 bytes are available, it only read the 2 bytes that are available.
    // If excepting to read multiple children writing to the same pipe, will have to create a loop to handle it.
    int fd[2];
    pid_t cPid;

    /* create a pipe */
    checkCall(pipe(fd), "pipe");

    srand(time(NULL));

    /* fork */
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

    exit(EXIT_SUCCESS);
}
