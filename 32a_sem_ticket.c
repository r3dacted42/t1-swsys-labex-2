/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

32. Write a program to implement semaphore to protect any critical section.
    a. rewrite the ticket number creation program using semaphore <---
    b. protect shared memory from concurrent write access
    c. protect multiple pseudo resources ( may be two) using counting semaphore
    d. remove the created semaphore
========================================================================================
*/

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct ticket {
    int ticket_num;
};

void init_tkt();

int main(int argc, char **argv) {
    key_t key = ftok(".", 't');
    int semid = semget(key, 1, 0);
    if (semid >= 0) printf("got binary semaphore with id: %d\n", semid);
    else {
        perror("semget failed with: ");
        return -1;
    }
    struct sembuf buf = {0, -1, 0};
    printf("trying to enter critical section...\n");
    semop(semid, &buf, 1);
    // critical section starts
    int fd = open("./32a.db", O_RDWR);
    if (fd < 0) {
        init_tkt();
        fd = open("./32a.db", O_RDWR);
    }
    struct ticket tkt;
    read(fd, &tkt, sizeof(tkt));
    printf("current ticket value: %d\n", tkt.ticket_num);
    tkt.ticket_num++;
    printf("incremented to: %d\n", tkt.ticket_num);
    lseek(fd, 0, SEEK_SET);
    write(fd, &tkt, sizeof(tkt));
    close(fd);
    printf("press enter to exit critical section...");
    getchar();
    // critical section ends
    buf.sem_op = 1;
    semop(semid, &buf, 1);
    printf("exited critical section!\n");

    return 0;
}

void init_tkt() {
    struct ticket tkt = { 0 };
    int fd = open("./32a.db", O_WRONLY | O_CREAT, 0666);
    write(fd, &tkt, sizeof(tkt));
    close(fd);
}

/*
Sample Execution:
((must run 31a_sem_bin.c to make sure the binary semaphore exists))
((use argument 't' to create new semaphore for task))

-- first terminal
$ runc 32a_sem_ticket.c 
got binary semaphore with id: 0
trying to enter critical section...
current ticket value: 2
incremented to: 3
press enter to exit critical section...

-- second terminal
$ runc 32a_sem_ticket.c
got binary semaphore with id: 0
trying to enter critical section...

-- press enter on first terminal
exited critical section!

-- second terminal proceeds
current ticket value: 3
incremented to: 4
press enter to exit critical section...

-- press enter to finish
exited critical section!

*/