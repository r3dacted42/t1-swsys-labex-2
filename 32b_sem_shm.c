/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

32. Write a program to implement semaphore to protect any critical section.
    a. rewrite the ticket number creation program using semaphore
    b. protect shared memory from concurrent write access <---
    c. protect multiple pseudo resources ( may be two) using counting semaphore
    d. remove the created semaphore
========================================================================================
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct data {
    pid_t lmpid;
    time_t lmtime;
    char buf[1024];
};

int main(int argc, char **argv) {
    key_t key = ftok(".", 's');
    int semid = semget(key, 1, 0);
    if (semid >= 0) printf("got binary semaphore with id: %d\n", semid);
    else {
        perror("semget failed with: ");
        return -1;
    }
    int shmid = shmget(key, sizeof(struct data), IPC_CREAT | 0744);
    if (shmid >= 0) printf("got shared memory segment (%ld bytes) with id: %d\n", sizeof(struct data), shmid);
    else {
        perror("shmget failed with: ");
        return -1;
    }
    char ch = 0;
    while (ch != 'r' && ch != 'w')
    {
        printf("pick whether you want to read or write to the shmem? [r/w]: ");
        scanf("%c", &ch);
        getchar();
    }
    struct data *shmem = (struct data*)shmat(shmid, NULL, 0);
    struct sembuf buf = {0, -1, 0};
    printf("trying to enter critical section...\n");
    semop(semid, &buf, 1);
    if (ch == 'w') {
        // critical section starts
        printf("please enter new data to store in buffer:\n");
        scanf("%[^\n]", shmem->buf);
        shmem->lmpid = getpid();
        shmem->lmtime = time(NULL);
        getchar(); // remove pendng \n
        printf("data written to shmem buffer!\n");
        printf("press enter to exit critical section...");
        getchar();
        // critical section ends
        buf.sem_op = 1;
        semop(semid, &buf, 1);
        printf("exited critical section!\n");
    } else {
        buf.sem_op = 1;
        semop(semid, &buf, 1);
        printf("data read from shared memory:\n");
        printf("last modified by pid: %d\n", shmem->lmpid);
        printf("last modified at time: %ld\n", shmem->lmtime);
        printf("stored buffer: %s\n", shmem->buf);
    }
    shmdt(shmem);

    return 0;
}

/*
Sample Execution:
((must run 31a_sem_bin.c to make sure the binary semaphore exists))
((use argument 's' to create new semaphore for task))

-- use semaphore when writing
$ runc 32b_sem_shm.c 
got binary semaphore with id: 2
got shared memory segment (1040 bytes) with id: 0
pick whether you want to read or write to the shmem? [r/w]: w
trying to enter critical section...
please enter new data to store in buffer:
semaphores are cool, but i like shmem better :)
data written to shmem buffer!
press enter to exit critical section...
exited critical section!

-- concurrent reads are allowed
$ runc 32b_sem_shm.c 
got binary semaphore with id: 2
got shared memory segment (1040 bytes) with id: 0
pick whether you want to read or write to the shmem? [r/w]: r
trying to enter critical section...
data read from shared memory:
last modified by pid: 72373
last modified at time: 1726948164
stored buffer: semaphores are cool, but i like shmem better :)

*/