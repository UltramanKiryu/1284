#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <malloc.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>

//#include "binary_sem.h"
#include <sys/shm.h>
#include <sys/sem.h>

#define READER 0
#define WRITER 1

/* define the struct that will represent the organization of our shared memory */
// We're gonna do producer consumer again
struct mSeg
{
    int numOfVals;
    int vals[100];
};

int checkCall(int val, char *msg)
{
    if (val == -1)
    {
        if (errno == EINTR) return -1;
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return val;
}
// Generates n random values, stores both n and the values generated in shared memory
// signals the consumer when done (using semaphores)
void producer()
{
    key_t sharedMemKey, semaphoreKey;
    int semaphoreID, sharedMemID;

    struct mSeg *attachedSharedMem;
    // generate two keys (ftok)
    // These both use the i-node of the "key" file, and the int associated with the characters 'm' and 's'
    sharedMemKey = ftok("./key",'m');
    semaphoreKey = ftok("./key",'s');

    // create the shared memory
    sharedMemID = checkCall(shmget(sharedMemKey, sizeof(struct mSeg), IPC_CREAT | S_IRUSR | S_IWUSR), "shmget");

    // create the semaphore
    semaphoreID = checkCall(semget(semaphoreKey, 2, IPC_CREAT | S_IRUSR | S_IWUSR), "shmget");

    // initialize the values of the semaphore ...
    // we will use semaphore 0 to be the reader
    // we will use semaphore 1 to be the writer

    // we need to init the reader to "in use"
    initSemInUse(semaphoreID, READER);
    // we need to init the writer to "available"
    initSemAvailable(semaphoreID, WRITER);

    // attach the shared memory
    attachedSharedMem = (struct mSeg *) shmat(sharedMemID, NULL, 0);

    // The following line is needed because shmat doesn't just return -1 on error,
    // it returns "(void *) -1" on error.
    if (attachedSharedMem == (void *) -1) checkCall(-1, "shmat");

    // reserve the writer the semaphore
    reserveSem(semaphoreID, WRITER);

    attachedSharedMem->numOfVals = (rand() % 100) + 1; // Generates the number of values to generate

    // create the values and store each in the vals array
    int total = 0;
    for (int i = 0; i < attachedSharedMem->numOfVals; i++)
    {
        attachedSharedMem->vals[i] = rand() % 5000;
        total += attachedSharedMem->vals[i];
    }
    printf("Producer total: %d\n", total);

    releaseSem(semaphoreID, READER); // release the reader semaphore

    reserveSem(semaphoreID, WRITER); // reserve the writer semaphore

    shmdt(attachedSharedMem); // detach the shared memory

    // delete the semaphores and shared memory
    checkCall(shmctl(sharedMemID, IPC_RMID, NULL), "shmctl");
    checkCall(semctl(semaphoreID, 0, IPC_RMID), "semctl");

    printf("Producer exiting...\n\n");
    exit(EXIT_SUCCESS);
}
// Waits for a datum to be present in a segment of shared memory,
// reads and sums those values, outputs those values
void consumer()
{
    key_t sharedMemKey, semaphoreKey;
    int semaphoreID, sharedMemID;
    int total = 0;
    struct mSeg *attachedSharedMem;

    sharedMemKey = ftok("./key",'m');
    semaphoreKey = ftok("./key",'s');
    // generate two keys

    // retrieve the semaphores and shared memory
    sharedMemID = checkCall(shmget(sharedMemKey, 0, 0), "shmget");
    semaphoreID = checkCall(semget(semaphoreKey, 0, 0), "semget");

    // reserve the reader semaphore
    reserveSem(semaphoreID, READER);

    attachedSharedMem = (struct mSeg *) shmat(sharedMemID, NULL, 0); // attach the shared memory

    if (attachedSharedMem == (void *) -1) checkCall(-1, "shmat");

    // read the values and create the total
    for (int i = 0; i < attachedSharedMem->numOfVals; i++)
    {
        total += attachedSharedMem->vals[i];
    }

    printf("Consumer Total = %d\n", total);

    releaseSem(semaphoreID, WRITER); // release the writer semaphore

    shmdt(attachedSharedMem); // detach the shared memory

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (!strcmp(argv[0], "./consumer")) { consumer(); return 0;}
    if (!strcmp(argv[0], "./producer")) { producer(); return 0;}
}
