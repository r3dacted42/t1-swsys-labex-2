/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

31. Write a program to create a semaphore and initialize value to the semaphore.
    a. create a binary semaphore <---
    b. create a counting semaphore
========================================================================================
*/

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

// union definition
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int main(int argc, char ** argv) {
    char c = 'b';
    if (argc > 1) c = argv[1][0];
    key_t key = ftok(".", c);
    int semid = semget(key, 1, IPC_CREAT | 0744);
    if (semid >= 0) printf("created binary semaphore with id: %d\n", semid);
    else {
        perror("semget failed with: ");
        return -1;
    }
    int semval;
    if ((semval = semctl(semid, 0, GETVAL)) < 0) {
        perror("semctl failed during GETVAL: ");
        return -1;
    }
    printf("current value of semaphore: %d\n", semval);
    union semun semu;
    semu.val = 1;
    if (semctl(semid, 0, SETVAL, semu) < 0) {
        perror("semctl failed during SETVAL: ");
        return -1;
    }
    printf("set value of semaphore to %d\n", semu.val);

    return system("ipcs --sem");
}

/*
Sample Execution:

-- no args
$ runc 31a_sem_bin.c 
created binary semaphore with id: 0
current value of semaphore: 0
set value of semaphore to 1

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x62205924 0          r3dacted42 744        1

-- with custom project id character
$ runc 31a_sem_bin.c s
created binary semaphore with id: 2
current value of semaphore: 0
set value of semaphore to 1

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     
0x62205924 0          r3dacted42 744        1         
0x73205924 1          r3dacted42 744        1

*/