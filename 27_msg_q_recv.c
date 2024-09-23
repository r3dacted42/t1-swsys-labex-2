/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

27. Write a program to receive messages from the message queue.
    a. with 0 as a flag
    b. with IPC_NOWAIT as a flag
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
    int mflag = 0;
    long mtype = 0;
    if (argc >= 2) {
        for (int i = 0; argv[1][i] != 0; i++) mtype = mtype * 10 + (argv[1][i] - 48);
        printf("will try to find message of type %ld\n", mtype);
    } 
    if (argc >= 3) {
        printf("will use IPC_NOWAIT flag\n");
        mflag = IPC_NOWAIT;
    }
    msg_struct msg;
    int rcv = msgrcv(mqid, &msg, sizeof(msg.mtext), mtype, mflag);
    if (rcv > 0) {
        printf("message received from message queue! (%d bytes):\n", rcv);
        printf("mtype: %ld\nmtext: %s\n", msg.mtype, msg.mtext);
    }
    else
        perror("msgrcv failed with: ");
    printf("current status of queue:\n");
    return system("ipcs --q");
}

/*
Sample Execution:

-- no args (flag = 0)
$ runc 27_msg_q_recv.c
msg queue key: 1629509924, id: 3
message received from message queue! (512 bytes):
mtype: 1
mtext: sample message @ 1726897853
current status of queue:

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61205924 3          r3dacted42 666        1024         2

-- giving mtype only (flag = 0)
$ runc 27_msg_q_recv.c 5
msg queue key: 1629509924, id: 3
will try to find message of type 5
message received from message queue! (512 bytes):
mtype: 5
mtext: sample message @ 1726900666
current status of queue:

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61205924 3          r3dacted42 666        512          1

-- giving type and IPC_NOWAIT (random second arg)
$ runc 27_msg_q_recv.c 5 n
msg queue key: 1629509924, id: 3
will try to find message of type 5
will use IPC_NOWAIT flag
message received from message queue! (512 bytes):
mtype: 5
mtext: sample message @ 1726900676
current status of queue:

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61205924 3          r3dacted42 666        0            0

*/