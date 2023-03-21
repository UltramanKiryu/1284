#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<time.h>
#include <pthread.h>
struct argValz
{
  int low;
int high;
int count;
int chunk;
};
void *startProd(void *arg)
{
    int count =0;
    int chuck =0;
    int val=0;
    struct timespec ts;
    struct argValz *argz=(struct argValz*)arg;
    ts.tv_sec=0;
    ts.tv_nsec=500;
    while (1) {
        if(count ==argz->count)break;
        assertErr(pthread_mutex_lock(&mtx),"pthread_murtex_lock");
        for(chunk=0,chuck <argz->chunk;chuck++)
        {
            sharedVal[avail]=genRand(argz->low,argz->high);
        }
    }
}
int main()
{
    struct argValz argz;
    pthread_t t1;
    int s =0;
    int count =0;
    srand(time(NULL));
    argz.low=0;
    argz.high=0;
    argz.count=0;
    argz.chunk=0;
    sharedVal = (int *) calloc(argz.count, sizeof (int), );
    if(sharedVal== NULL)
    {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    assertErr(pthread_create(&t1,NULL, startProd,&arg1),"pthread_create");

    return 0;
}
