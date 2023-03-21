#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#define BUF_SIZE 1024

union ISTR
{
    int val;
    char bytes[4];
};


char *dupString(const char *val)
{
  int len = strlen(val);
  char *outStr = (char *) calloc(len + 1, sizeof(char));
  if (outStr == NULL)
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }
  strcpy(outStr, val);
  return outStr;
}
int main(int argc, char *argv[])
{
    char *outFile = NULL;
    char tt,phrse;
    int att=0,aw=0;
    char buf[2];
    union ISTR in;
    if (argc != 1)
       {
         perror("malformed call to File");
         exit(EXIT_FAILURE);
       }
    /*
    if(argc==2)
    {
        tt= atoi(argv[0]);
       phrse=atoi(argv[1]);
       write(STDOUT_FILENO,"Enter in a phrase",BUF_SIZE);

    }
*/
    if(argc == 3 ) //wc <file>
    {

       tt= atoi(argv[0]);
      phrse=atoi(argv[1]);
      outFile = dupString(argv[2]);
    }
    if(argc == 5)// wc -c <file> or wc -w <file>
    {
        tt= atoi(argv[0]);
       phrse=atoi(argv[1]);
       if(atoi(argv[2])=='-')
       {
           if(atoi(argv[3])=='w')
           {
               att =0;
           }
           if(atoi(argv[3])=='c')
           {
               att =1;
           }
       }
       outFile = dupString(argv[4]);
    }
    if(argc==6)// wc -c -w <file>
    {
        tt= atoi(argv[0]);
       phrse=atoi(argv[1]);
       if(atoi(argv[2])=='-')
       {
           att =1;
           aw = 1;
       }

       outFile = dupString(argv[4]);
    }


}
