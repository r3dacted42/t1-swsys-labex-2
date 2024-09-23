/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

30. Write a program to create a shared memory.
    a. write some data to the shared memory <---
    b. attach with O_RDONLY and check whether you are able to overwrite.
    c. detach the shared memory
    d. remove the shared memory
========================================================================================
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main() {
    key_t key = ftok(".", 'a');
    int shmid = shmget(key, 0, 0);
    if (shmid >= 0) printf("got shared memory segment (1024 bytes) with id: %d\n", shmid);
    else {
        perror("shmget failed with: ");
        return -1;
    }
    void *shmem = shmat(shmid, NULL, SHM_W);
    long int wr = sprintf((char*)shmem, "some text written to the shared memory.");
    shmdt(shmem);
    printf("wrote %ld bytes to shared memory\n", wr);
    
    return 0;
}

/*
Sample Execution:

$ runc 30a_shm_write.c 
got shared memory segment (1024 bytes) with id: 1
wrote 39 bytes to shared memory

*/