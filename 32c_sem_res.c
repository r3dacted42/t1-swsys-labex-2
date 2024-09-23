/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

32. Write a program to implement semaphore to protect any critical section.
    a. rewrite the ticket number creation program using semaphore
    b. protect shared memory from concurrent write access
    c. protect multiple pseudo resources ( may be two) using counting semaphore <---
    d. remove the created semaphore
========================================================================================
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv) {
    key_t key = ftok(".", 'r');
    int semid = semget(key, 1, 0);
    if (semid >= 0) printf("got binary semaphore with id: %d\n", semid);
    else {
        perror("semget failed with: ");
        return -1;
    }
    printf("how much of the resource to allocate? [max 5]: ");
    int alloc = 0;
    scanf("%d", &alloc);
    getchar();
    if (alloc > 5) alloc = 5;
    struct sembuf buf = {0, -1 * alloc, 0};
    printf("trying to enter critical section...\n");
    /* allocate imaginary shared resource */
    semop(semid, &buf, 1);
    // critical section starts
    int resval;
    if ((resval = semctl(semid, 0, GETVAL)) < 0) {
        perror("semctl failed while fetching semaphore value: ");
        return -1;
    }
    printf("remaining available resource: %d\n", resval);
    printf("press enter to release resource...");
    getchar();
    // critical section ends
    buf.sem_op = alloc;
    semop(semid, &buf, 1);
    printf("exited critical section!\n");

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