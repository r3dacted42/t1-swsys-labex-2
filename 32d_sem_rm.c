/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       22 September 2024

32. Write a program to implement semaphore to protect any critical section.
    a. rewrite the ticket number creation program using semaphore
    b. protect shared memory from concurrent write access
    c. protect multiple pseudo resources ( may be two) using counting semaphore
    d. remove the created semaphore <---
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

void remove_sem(char proj_id) {
    key_t key = ftok(".", proj_id);
    int semid = semget(key, 1, 0);
    if (semid >= 0) printf("got semaphore with id: %d\n", semid);
    else {
        perror("semget failed with: ");
    }
    if (semctl(semid, 0, IPC_RMID) < 0) {
        perror("semctl failed while removing semaphore: ");
    } else {
        printf("successfully removed semaphore!\n");
    }
}

int main(int argc, char **argv) {
    remove_sem('t');
    remove_sem('s');
    remove_sem('r');
    // also remove shm used in part b
    int shmid = shmget(ftok(".", 's'), 0, 0);
    printf("got shm with id: %d\n", shmid);
    if (shmctl(shmid, IPC_RMID, NULL) < 0) printf("shmctl failed while removing shm: ");
    else printf("successfully removed shm!\n");

    return 0;
}

/*
Sample Execution:
((must run 31b_sem_cnt.c to make sure the binary semaphore exists))
((use arguments 'r 5' to create new semaphore for task))

-- first terminal
$ runc 32c_sem_res.c 
got binary semaphore with id: 6
how much of the resource to allocate? [max 5]: 3
trying to enter critical section...
remaining available resource: 2
press enter to release resource...

-- second terminal
$ runc 32c_sem_res.c
got binary semaphore with id: 6
how much of the resource to allocate? [max 5]: 2
trying to enter critical section...
remaining available resource: 0
press enter to release resource...

-- third terminal
$ runc 32c_sem_res.c
got binary semaphore with id: 6
how much of the resource to allocate? [max 5]: 3
trying to enter critical section...

-- press enter on first terminal
exited critical section!

-- third terminal
remaining available resource: 0
press enter to release resource...

*/