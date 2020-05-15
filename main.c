#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <semaphore.h>

int main()
{
    int i;              // loop variable
    key_t shmkey;       // shared memory key
    int shmid;          // shared memory id
    sem_t* sem;         // synch semaphore
    pid_t pid;          // pid for fork operation
    int* p;             // shared variable
    unsigned int n;     // fork count
    unsigned int value; // semaphore value
    
    // directory and number, it's to generate key
    shmkey = ftok("/Users/tyom/Desktop/semaphorei/main.c", 5);
    printf("shmkey for p = %d\n", shmkey);

    // initialize memory
    shmid = shmget(shmkey, sizeof(int), 0644 | IPC_CREAT);

    if (shmid < 0)
    {
        perror("shmget\n");
        exit(1);
    }

    // attach p to shared memory
    p = (int*)shmat(shmid, NULL, 0);
    *p = 0;

    printf("p = %d is allocated in shared memory. \n\n", *p);

    printf("Number of children you want to fork: ");
    scanf("%u", &n);

    printf("Semaphore value: ");
    scanf("%u", &value);
    
    // Semaphore initialization. The semaphore name is Sem. 
    sem = sem_open("Sem", O_CREAT | O_EXCL, 0644, value);

    // unlink prevents the semaphore existing forever
    sem_unlink("Sem");
    printf("semaphores initialized\n\n");
    
    // Forking 
    for (i = 0; i < n; ++i)
    {
        pid = fork();
        if (pid < 0)
            printf("Fork error\n");
        else if (pid == 0)
            break; // child processes
    }

    // pid > 0 represents parent process
    if (pid != 0)
    {
        // wait for all children to exit , 
        // this is to be ensured as the problem of orphans raise
        while (pid = waitpid(-1, NULL, 0))
        {
            if (errno == ECHILD)
                break;
        }

        printf("\nParent: All children have exited.\n");
        
        // detach shared memory
        shmdt(p);
        shmctl(shmid, IPC_RMID, 0);

        // destroy semaphore
        sem_destroy(sem);
        exit(0);
    }
    else
    {
        sem_wait(sem); // P operation
        printf("Child(%d) is in critical section \n", i);
        sleep(1);

        // increment *p by 0, 1 or 2 based on i
        *p += i % 3;
        printf("Child(%d) new value of *p = %d.\n", i, *p);
        
        sem_post(sem); // V operation
        exit(0);
    }


    return 0;
}
