/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

26. Write a program to send messages to the message queue. Check $ipcs -q
========================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include "msg_struct.c"
#include <stdlib.h>
#include <time.h>

int main() {
    key_t key = ftok(".", 'a');
    int mqid = msgget(key, IPC_CREAT | 0666);
    printf("msg queue key: %d, id: %d\n", key, mqid);
    msg_struct msg;
    msg.mtype = 1;
    sprintf(msg.msg, "sample message @ %ld", clock());
    if (!msgsnd(mqid, &msg, sizeof(msg), IPC_NOWAIT))
        printf("message sent to message queue!\n");
    else
        perror("msgsnd failed with: ");
    
    return system("ipcs --q");
}

/*
Sample Execution:

$ runc 26_msg_q_send.c 
msg queue key: 1629509924, id: 2
message sent to message queue!

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61205924 2          r3dacted42 666        136          1

*/