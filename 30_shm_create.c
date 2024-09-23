/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

30. Write a program to create a shared memory. <---
    a. write some data to the shared memory
    b. attach with O_RDONLY and check whether you are able to overwrite.
    c. detach the shared memory
    d. remove the shared memory
========================================================================================
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t key = ftok(".", 'a');
    int shmid = shmget(key, 1024, IPC_CREAT | 0744);
    if (shmid >= 0) printf("created shared memory segment (1024 bytes) with id: %d\n", shmid);
    else {
        perror("shmget failed with: ");
        return -1;
    }
    
    return system("ipcs --shm");
}

/*
Sample Execution:

$ runc 30_shm_create.c 
created shared memory segment (1024 bytes) with id: 1

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x61205924 1          r3dacted42 744        1024       0

*/