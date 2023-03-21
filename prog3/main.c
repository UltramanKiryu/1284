#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
//using system child

// get ppid();
#define BUF_SIZE 4

union ISTR
{
    int val;
    char bytes[4];
};
int myPrint(const char*str)
{
    int len = strlen(str);
    int numWrite=0;
    numWrite=write(STDOUT_FILENO,str,len);
    if(numWrite<1)
    {
        return 0;
    }
    return 1;
}
void signalHandlerP(int sig) // parent
{
    char other[1024] = { 0 };
    int l=0, u=0;
    if(sig == SIGCHLD)
    {
        int p=0, status=0;
        while ((p=waitpid(-1,&status, WNOHANG))>0)
        {}
        if(p==-1)
        {
            if(errno ==ECHILD)
            {
                exit(EXIT_SUCCESS);
            }
            perror("waitpad");
            exit(EXIT_FAILURE);
        }
    }
    if(sig == SIGINT)
    {
       char yorn[BUF_SIZE];
       myPrint("\nExit: Are you sure(Y/N)? ");
       read(STDIN_FILENO,yorn,BUF_SIZE);
       if(yorn[0]=='Y')
       {
           exit(EXIT_SUCCESS);
       }
       else
       {
       return;
       }
    }
    if (sig ==SIGUSR1)
      {
        l++;
        printf("the child has genreated %d",l);
        printf(" values less than 25\n");
        //exit(EXIT_SUCCESS);
      }
    if (sig ==SIGUSR2)
      {
        u++;
        printf("the child has genreated %d",u);
        printf(" values greater than 75\n");
        //exit(EXIT_SUCCESS);
      }
    if (sig == SIGHUP)
      {
        exit(EXIT_SUCCESS);
      }
}
void signalHandlerC(int sig) //child
{
    if (sig == SIGALRM)
      {

      }
  if (sig == SIGTERM)
    {
      exit(EXIT_SUCCESS);
    }
}
int main()
{
    int fd;
    union ISTR in;
    //mode_t perms =S_IRUSR|_S_IWUSR|S_IRGRP;
    int inBytes;

fd =open("flowData.dat",O_RDONLY);
if(fd ==-1)
{
    exit(EXIT_FAILURE);
}
    return 0;
}
