#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
/*
 * Cyber Security
 * Department of Computer
 * science and Engineering
 * George Trawick Ph.d
 * Departemtn head and Professor
 * Computer Science and Engineering
 *
 * 93% of breadches had a finacial and/or espionage motive
 * 98% of data breaches, targeted systems were compromised within minutes
 * 83% of time, those breaches were not discovered for weeks
 * 7m average consolidated total cost of a US data breach in 2016
 * 221
 *
 * april 22
 *
 * */
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
void consumer()
{
    char wor[40];
    int fd;
    initFIFO("FIFOval");

    fd = checkCall(open("FIFOval", O_RDONLY), "open");
    checkCall(read(fd, &wor, sizeof(wor)), "read from the pipe");
     printf("Consumer: %s\n",wor);
     close(fd);
}
int main()
{
    // use to open the program to recieve the data form the FIFO
   consumer();
}
