/*
 Name: Andrew Banks
 NetID: alb1424
 Compiler Used:
 Program Descriction:
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#define BUF_SIZE 4

union ISTR
{
  int val;
  char bytes[4];
};

int main(int argc, char *argv[])
{
   char qe[1024];
    char *args[] = {"myRand", NULL};
   union ISTR in;
   int fd,status=0,inBytes,total=0,average=0;
   pid_t p;
   p=fork();
   switch (p) {
   case-1:
       perror("fork");
       exit(EXIT_FAILURE);
    case 0:
       //run execl funtions
       execve("./myRand",args,NULL);
       exit(EXIT_SUCCESS);
   default:
       wait(&status);
       if (WIFEXITED(status)){
             int returned = WEXITSTATUS(status);
             //printf("exiting normally with %d\n",returned);
             sprintf(qe,"data%d.dat",returned);
       };
       fd =open(qe,O_RDONLY);
       if(fd ==-1)
       {
           exit(EXIT_FAILURE);
       }
       for( int i = 0 ;i<60; i++ )
       {
           in.val=0;
           inBytes=read(fd,in.bytes, 4);
           if(inBytes==-1)
           {
               exit(EXIT_FAILURE);
           }
           printf("%d\n",in.val);

           // adding to the total
           total=total+in.val;
       }
       close(fd);

       // display the average
       average=total/60;
       printf("Average: %d\n",average);;
      }


}
