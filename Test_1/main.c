/* All of the includes for the project go here …
 * those includes must support signals, interval timers,
 * read, open, and close. You will also need support for
 * error numbers
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include<time.h>
#include<sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
/* Problem 1  */

#define BUF_SIZE 1024

static int timed;

/* the myPrint function takes a constant c-string
 * and outputs it to STDOUT using write
 * myPrint returns 0 on failure and 1 on success
 */
int myPrint(const char *str)
{
/* Problem 2 */
    write(1,str,20);
    return 1;
}

/* the myPrintInt function takes a constant int
 * and outputs it to STDOUT using write
 * myPrintInt returns 0 on failure and 1 on success
 */
int myPrintInt(const int val)
{
    char na[2];
/* Problem 3 */
    sprintf(na,"%d",val);
    if(write(1,na,2)==-1)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}

/* implement the signal hadler below ...
 * use the provided prototype
 * It must handle two signals, SIGINT and SIGALRM
 */
void signalHandler(int sig)
{
/* Problem 4 */
    char buf[22];
    int uread;
    if(sig == SIGINT)
    {
        write(1,"Do you want to exit:",20);
        uread=read(0,buf,1);
        if(uread=='n')
        {
            printf("why");
        }
        if(uread=='Y')
        {
            write(1,"okay the test will now conclude",28);
            exit(EXIT_SUCCESS);
        }
    }
    if(sig == SIGALRM)
    {
        timed=1;
    }

}
/* This function reads a line of text from a file
 * we are simulating another functions behavior here ..
 * Return a 0 if no characters were read, return a 1 otherwise
 */
int readLine(int fd, char *line)
{

    char tit[55];
    char tt;
/* Problem 5 */
    while (1) {
        if(read(fd,line,1)==0)
        {
            write(1,line,10);
        }
    }


}



/* This function reads a question answer pairing
 * from the provided pair of file descriptors
 * It returns 0 if the files are empty
 * and 1 if if successfully reads the pairing
 */

int readQA(int questFd, int ansFd, char *quest, char *ans)
{
  if (readLine(questFd,quest) == 0) return 0;
  if (readLine(ansFd, ans) == 0) return 0;
  return 1;
}

int main(int argc, char *argv[])
{

  int numRead = 0;
  int numWrite = 0;
  int question = 1;
  int correct = 0;
  char buf[BUF_SIZE];
  char quest[BUF_SIZE];
  char ans[BUF_SIZE];
  int questFd, ansFd;
 /* Problem 6a*/

  struct sigaction hndlr;
  struct itimerval tvOn;
  struct itimerval tvOff;
  struct timespec ts;
  ts.tv_sec = 0;

 /* Problem 6b */
  hndlr.sa_handler = signalHandler;
  sigemptyset(&hndlr.sa_mask);
  hndlr.sa_flags = 0;

/* Problem 6c */

  tvOn.it_interval.tv_sec=30;
  if(setitimer(ITIMER_REAL, &tvOn, NULL)==-1)
  {
      perror("setitmer");
      exit(EXIT_FAILURE);
  }
/* Problem 6d */
  tvOff.it_interval.tv_sec=0;
  tvOff.it_interval.tv_usec=0;

  if(setitimer(ITIMER_REAL, &tvOff, NULL)==-1)
  {
      perror("settimer");
      exit(EXIT_FAILURE);
  }

/* Problem 7 */
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



/* Problem 8  */

   /* this loop handles the Q/A stuff
    * I have included some of it to make you life simpler
    * I have also left some commnents to assist you as well
    *
    * read the first question, answer pairing prior to entering the loop
    */
  questFd=open("quest.txt",O_RDONLY);
  if(questFd==-1)
  {
      perror("open answer");
      exit(EXIT_FAILURE);
  }
  ansFd=open("ans.txt",O_RDONLY);
  if(ansFd==-1)
    {
        perror("open question");
        exit(EXIT_FAILURE);
    }
    readQA(questFd, ansFd, quest, ans);
  while (1)
    {
      /* output the current question */
      myPrint("#");
      myPrintInt(question);
      myPrint(" ");
      myPrint(quest);
      myPrint("? ");
      /* we will set the timedout flag to 0, since it hasn't yet */
      timed = 0;

      /* now set the interval timer prior to reading in the user's response */
       tvOn.it_interval.tv_usec=0;

 /*  Problem 9 */

      /* read in the user's response, this is systems programming so don't use
       * scanf */
      read(0,buf,10);

 /* Problem 10 */

      /* test to see if the user responded and if an error has occurred
       * an error can actually occur as part of the functionality of this program
       * both SIGINT and SIGALRM will cause the read call to return a -1
       * this can be recognized by testing for a specific error number ...
       * The error is known as interrupted systems call
       * Should this be the case, do the following ....
       * If the read call was interrupted and the timedout flag isn't set
       * just continue
       * if the timedout flag was set, inform the user that time is up
       * then go to the next question
       */
      if (numRead == 0) break;
      if (numRead == -1)
    {
      if (errno == EINTR)
        {
          if (timed)
        {
          myPrint("\nTime's up, next question\n");
          if (readQA(questFd, ansFd, quest, ans) == 0) break;
          question++;
        }
          continue;
        }
      perror("read");
      exit(EXIT_FAILURE);
    }
      /* disable the timer here */
/* Problem 11*/

      /* we will convert the buf being read in to a c-string by tacking on a 0 */
    buf[numRead-1] = 0;
    /* check the answer */
    if (strcmp(buf,ans) == 0)
      {
        correct++;
        myPrint("\ncorrect\n");
      } else
      {
        myPrint(ans);
        myPrint("\nwrong\n");
      }
    /* read the next question .. break if there are no more questions */
    if (readQA(questFd, ansFd, quest, ans) == 0) break;

    question++;
    }

  myPrint("final score is ");
  myPrintInt(correct);
  myPrint(" out of ");
  myPrintInt(question);

/* Problem 12 */
  close(questFd);
  close(ansFd);
  exit(EXIT_SUCCESS);
}

