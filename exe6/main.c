#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include<pthread.h>

/* implments three threads
 * prints evens
 * print odds
 * main thread
 */
int threadError(int err, char *str)
{
    if(err<0)
    {
        errno=err;
        perror(str);
        exit(EXIT_FAILURE);
    }
    return err;
}
void*evenThread(void*argc)
{
    int n=0;
    struct timespec tv;
    tv.tv_sec=1;
    tv.tv_nsec=0;
    for(n=0;n<61;n+=2)
    {
        printf("E: %d\n",n);
        nanosleep(&tv,NULL);
    }
    pthread_exit(NULL);
}
void*oddThread(void*argc)
{
    int n=1;
    struct timespec tv;
    tv.tv_sec=1;
    tv.tv_nsec=0;
    for(n=1;n<61;n+=2)
    {
        printf("O: %d\n",n);
        nanosleep(&tv,NULL);
    }
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    pthread_t tid[2];
    struct timespec tv;
    tv.tv_sec=20;
    tv.tv_nsec=0;
   //creates the threads
    threadError(pthread_create(&tid[0],NULL,evenThread,NULL),"pthread_create");
    threadError(pthread_create(&tid[1],NULL,oddThread,NULL),"pthread_create");
    //detach threads
    threadError(pthread_detach(tid[0]),"phtread_detach");
    threadError(pthread_detach(tid[1]),"phtread_detach");

    //join the threads
    threadError(pthread_join(tid[0],NULL),"pthread_join");
    threadError(pthread_join(tid[1],NULL),"pthread_join");
    nanosleep(&tv,NULL);
    return 0;
}
