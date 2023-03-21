#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

/* global counter for this program */
int count = 0;

/* Problem 2: the signal handler goes here -- needs to support actions for both SIGINT and SIGALRM

as described above*/

void sigHandler(int sig)
{
    if(sig == SIGINT)
    {
        count+=5;
        printf("jell0");
    }
    if(sig == SIGALRM)
    {
        count -=25;
        printf("  h0");
    }
}

void checkCall(int vasl,const char *msg)
{
    if(vasl==-1)
    {
        perror("msg");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
    /* Problem 3a: declare variables -- you need to declare a sigaction and itimerval structure */
    struct sigaction hndlr;
    struct itimerval itmr;
    struct timespec ts;

    ts.tv_sec = 0; // how nanosleep works
    ts.tv_nsec = 3000000;
   /* Problem 3b: configure your sigaction structure

        set the handler to sigHandler

        set the mask to the empty mask

        set the flags to 0 */

  hndlr.sa_handler = sigHandler;
  sigemptyset(&hndlr.sa_mask);
  hndlr.sa_flags = 0;

   /* Problem 3c: configure you itimerval structure

        set the interval timer to 1 seconds, 0 micro seconds

        set the initial timer to 1 seconds, 0 micro seconds */

  itmr.it_interval.tv_sec=1;
  itmr.it_interval.tv_usec=0;
  itmr.it_value.tv_sec=1;
  itmr.it_value.tv_usec=0;



   /* Problem 4: use sigaction to set the dispositions for SIGINT and SIGALRM to sigHandler */
  if(sigaction(SIGINT,&hndlr, NULL)==-1)
  {
      perror("sigaction");
      exit(EXIT_FAILURE);
  }
  if(sigaction(SIGALRM, &hndlr, NULL)==-1)
  {
      perror("sigaction");
      exit(EXIT_FAILURE);
  }
  /* Problem 5: setup the timer */
if(setitimer(ITIMER_REAL, &itmr, NULL)==-1)
{
    perror("sigaction");
    exit(EXIT_FAILURE);
}

  /* This loop increments count every 2000 microseconds */
   for (count = 0;; count++)
   {
    if (count % 50 == 0) { printf("%d\n",count);}
    /* we are using nanosleep here because nanosleep is never implemented with SIGALRM

        make certain to include the correct files to support nanosleep */
    if(count < -500)break;

    nanosleep(&ts, NULL);
   }

}
/*
int count =0;
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

void sigHandler(int sig)
{
    char yorn[BUF_SIZE];
    int num,l=0, u=0;
    srand(time(NULL));
    num =rand()%100;
    if(sig == SIGINT)
    {
       myPrint("\nExit: Are you sure(Y/N)? ");
       read(STDIN_FILENO,yorn,BUF_SIZE);
       if(yorn[0]=='Y')
       {
           exit(EXIT_SUCCESS);
       }
       return;
    }

    if(sig == SIGALRM)
    {
        printf("%d\n",num);
        if(num<25)
        {
           myPrint("this workd");
            count=1;
        }
        if(num>75)
        {
            //myPrint("this");

        }
    }
    if(sig ==SIGUSR1)
    {
        printf("child has produce a value below 25\n");

        l++;
        printf("the child has genreated %d",l);
        printf(" values less than 25\n");

    }
    if(sig ==SIGUSR2)
    {
        printf("child has produce a value above 75\n");
    }

}
int checkCall(int flag, const char *msg){
    if (flag ==-1)
    {
        perror("msg");
        exit(EXIT_FAILURE);
    }
    return flag;
}
//critcal sections that we want oy one therad to be able to acess the
// detached therads cannot be reattaed to the process
// needs mutiple arguments, htey need to be stored asd a struct
// argc[0] = "la;
//argc[1] =la";
// argc[2] =""
//execlp("ls","ls","la","NULL");
int main()
{
    pid_t Pid;
    Pid=fork();
    struct sigaction hndlr;
    struct itimerval itmr;
    struct timespec ts;

    hndlr.sa_handler = sigHandler;
    sigemptyset(&hndlr.sa_mask);
    hndlr.sa_flags = 0;

    itmr.it_interval.tv_sec=1;
    itmr.it_interval.tv_usec=0;
    itmr.it_value.tv_sec=1;
    itmr.it_value.tv_usec=0;
    if(sigaction(SIGINT,&hndlr, NULL)==-1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGALRM, &hndlr, NULL)==-1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    if(setitimer(ITIMER_REAL, &itmr, NULL)==-1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    switch (Pid) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
     case 0:
        if(count ==1)
        {
            printf("less than 25\n");
            //sigaction(SIGUSR1, &hndlr,NULL);
             //raise(SIGUSR1);
        }

        exit(EXIT_SUCCESS);
        break;
    }
    while(1)
    {
        pause();
    }


    return 0;
}
*/
