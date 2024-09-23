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
#include "mq_msg_struct.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    key_t key = ftok(".", 'a');
    int mqid = msgget(key, IPC_CREAT | 0666);
    printf("msg queue key: %d, id: %d\n", key, mqid);
    msg_struct msg;
    msg.mtype = 1;
    if (argc > 1) {
        msg.mtype = 0;
        for (int i = 0; argv[1][i] != 0; i++) msg.mtype = msg.mtype * 10 + (argv[1][i] - 48);
    }
    sprintf(msg.mtext, "sample message @ %ld", time(NULL));
    if (!msgsnd(mqid, &msg, sizeof(msg.mtext), IPC_NOWAIT))
        printf("message of type %ld sent to message queue!\n", msg.mtype);
    else
        perror("msgsnd failed with: ");
    printf("current status of queue:\n");
    return system("ipcs --q");
}

/*
Sample Execution:

-- no args (default mtype = 1)
$ runc 26_msg_q_send.c 
msg queue key: 1629509924, id: 2
message of type 1 sent to message queue!
current status of queue:

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61205924 2          r3dacted42 666        512          1

-- with custom msg type
$ runc 26_msg_q_send.c 5
msg queue key: 1629509924, id: 2
message of type 5 sent to message queue!
current status of queue:

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61205924 2          r3dacted42 666        2560         5

*/