/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

24. Write a program to create a message queue and print the key and message queue id.
========================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main() {
    key_t key = ftok(".", 'a');
    int mqid = msgget(key, IPC_CREAT | 0666);
    printf("msg queue key: %d, id: %d\n", key, mqid);
    
    return 0;
}

/*
Sample Execution:

$ runc 24_msg_q_id.c 
msg queue key: 1629509924, id: 0

$ ipcs --q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x61205924 0          r3dacted42 666        0            0

*/