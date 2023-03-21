#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>

#define BUF_SIZE 1024
/*
 * set the union to 0
 * if(read(output.Fd, outBytes,2)!=2) * read in 2 bytes
 *outBytes.value
 *
 * gcc main.c name of other headers .c on the same command lines
 *
 * */
void listFiles(const char *dirpath)
{
    DIR *dirp;
    struct dirent *dp;
    int isCurrent;
    isCurrent= (strcmp(dirpath,".")==0);

    dirp = opendir(dirpath);
    if(dirp ==NULL)
    {
        perror("opendir");
        return;
    }
    while(1)
    {
        errno =0;
        dp =readdir(dirp);
        if(dp==NULL)
            break;
        if(strcmp(dp->d_name,".")==0)
            continue;
        if(!isCurrent)
            printf("%s\n",dirpath);
        printf("%s\n",dp->d_name);
      }

    if(errno != 0)
    {
        perror("readdir");
        exit(EXIT_FAILURE);
    }
    if(closedir(dirp)==-1)
        {
            perror("closedir");
        }
}


    int main(int argc, char *argv[])
    {
       if(argc ==1)
       {
           listFiles(".");
       }
       else
           for(argv++;*argv;argv++)
               listFiles(*argv);

       exit(EXIT_SUCCESS);
        return 0;
    }
