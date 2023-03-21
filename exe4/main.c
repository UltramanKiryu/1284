#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#define BUF_SIZE 1024
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
void signalHandlerP(int sig)
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

void signalHandlerC(int sig)
{
  if (sig == SIGTERM)
    {
      exit(EXIT_SUCCESS);
    }
}
int main()
{
   pid_t Pid;
   int num;
   srand(time(NULL));
   num =rand()%100;
   Pid=fork();
   struct sigaction saP;
   struct sigaction saC;

   saP.sa_handler = signalHandlerP;
   sigemptyset(&saP.sa_mask);
   saP.sa_flags = 0;

   saC.sa_handler = signalHandlerC;
   sigemptyset(&saC.sa_mask);
   saC.sa_flags = 0;

   if (sigaction(SIGCHLD, &saP, NULL) == -1)
     {
       perror("sigaction");
       exit(EXIT_FAILURE);
     }
   switch(Pid)
 {
 case -1: // if the fork fails
   perror("fork");
   exit(EXIT_FAILURE);
 case 0:// when the child
   if (sigaction(SIGHUP, &saP, NULL) == -1)
     {
       perror("sigaction");
       exit(EXIT_FAILURE);
     }
   printf("%d\n",num);
   if(num<25)
   {
      //printf("less than 25\n");
      sigaction(SIGUSR1, &saP,NULL);
       raise(SIGUSR1);
   }
   if(num>75)
   {
       //printf("greater than 75\n");
       sigaction(SIGUSR2, &saP,NULL);
        raise(SIGUSR2);
   }
   if(num>48&&num<51)
   {
       //printf("greater than 48 but less than 51\n");
       exit(EXIT_SUCCESS);
   }
   exit(EXIT_SUCCESS);
   break;
 }
   if (sigaction(SIGHUP, &saP, NULL) == -1)
     {
       perror("sigaction");
       exit(EXIT_FAILURE);
     }
   //pause
   while(1)
     {
       pause();
     }
    return 0;
}


