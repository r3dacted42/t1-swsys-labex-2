/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

30. Write a program to create a shared memory.
    a. write some data to the shared memory
    b. attach with O_RDONLY and check whether you are able to overwrite.
    c. detach the shared memory
    d. remove the shared memory <---
========================================================================================
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int shmid = -1;
    if (argc == 2) {
        shmid = 0;
        for (int i = 0; argv[1][i] != 0; i++) shmid = shmid * 10 + (argv[1][i] - 48);
        printf("will try to remove shmem segment with id: %d\n", shmid);
    } else {
        printf("please provide the id of the shmem segment to remove!\n");
        printf("usage: %s <shmid>\n", argv[0]);
        return -1;
    }
    if (!shmctl(shmid, IPC_RMID, NULL)) printf("successfully removed shmem segment!\n");
    else {
        perror("shmctl failed with: ");
        return -1;
    }
    
    return 0;
}

/*
Sample Execution:

-- no args
$ runc 30d_shm_rm.c 
please provide the id of the shmem segment to remove!
usage: ./run-1726912399.o <shmid>

-- shmid given as arg
$ runc 30d_shm_rm.c 1
will try to remove shmem segment with id: 1
successfully removed shmem segment!

-- already deleted shmid given
$ runc 30d_shm_rm.c 1
will try to remove shmem segment with id: 1
shmctl failed with: : Invalid argument

*/