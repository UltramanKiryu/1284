#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 4
union ISTR
{
  int val;
  char bytes[4];
};
int randInt(int low, int high)
{
  int rng = high - low;
  double scl = (((double) rand()) / ((double) RAND_MAX + 1));
  int offst = scl * rng;
  return low + offst;
}
int main(int argc, char *argv[])
{
    int ran,fd,X;
    char qe[1024];
    union ISTR in,out2,out;
    int outBytes,inBytes;
    int flag =O_RDWR|O_CREAT|O_TRUNC;
    //=O_WRONLY|O_CREAT|O_TRUNC;
    mode_t perms =S_IRUSR|S_IWUSR|S_IRGRP;
    srand(time(NULL));
    X =randInt(0,225);
    sprintf(qe,"data%d.dat",X);
    //write(STDOUT_FILENO, out, strlen(out));
    fd =open(qe,flag, perms);
    if(fd ==-1)
    {
        exit(EXIT_FAILURE);
    }

    for(int i =0; i<60;i++)
    {
        ran = randInt(0,100);
        out.val = ran;
        outBytes =write(fd,out.bytes,4);
        if(outBytes==-1)
        {

            close(fd);
            exit(EXIT_FAILURE);
        }
        //printf("%d\n",val);
    }
     close(fd);
     fd =open(qe,O_RDONLY);
     if(fd ==-1)
     {
         exit(EXIT_FAILURE);
     }
     /*
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
         //total=total+in.val;
     }
     close(fd);
     // exit with the number of the dataX.dat file
     */
     exit(X);
}
