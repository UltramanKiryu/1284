#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
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

void initFIFO(char *path)
{
    if (mkfifo(path, S_IRUSR | S_IWUSR) == -1)
    {
        if (errno == EEXIST) return;
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    return;
}
void producer()
{
    char wor[40];
    int fd;
    // making the FIFO
    initFIFO("FIFOval");

    fd = checkCall(open("FIFOval", O_WRONLY), "open");
    char *out = "Please enter text into the Producer:\n";
    write(STDOUT_FILENO, out, 38);
    read(STDIN_FILENO,wor,40);

    printf("Producer: %s\n",wor);
    checkCall(write(fd, &wor, sizeof(wor)), "write to the pipe");
    close(fd);
}

int main(int argc, char *argv[])
{
    // call the producer to write the into the producer
    producer();

    return 0;
}
