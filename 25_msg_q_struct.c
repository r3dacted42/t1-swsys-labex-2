/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

25. Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
    a. access permission
    b. uid, gid
    c. time of last message sent and received
    d. time of last change in the message queue
    d. size of the queue
    f. number of messages in the queue
    g. maximum number of bytes allowed
    h. pid of the msgsnd and msgrcv
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
    struct msqid_ds mqds;
    msgctl(mqid, IPC_STAT, &mqds);
    printf("a. access permission: %o\n", mqds.msg_perm.mode);
    printf("b. uid: %d, gid: %d\n", mqds.msg_perm.uid, mqds.msg_perm.gid);
    printf("c. time of last message sent: %ld, received: %ld\n", mqds.msg_stime, mqds.msg_rtime);
    printf("d. time of last change in the message queue: %ld\n", mqds.msg_ctime);
    printf("e. size of the queue: %ld\n", mqds.__msg_cbytes);
    printf("f. number of messages in the queue: %ld\n", mqds.msg_qnum);
    printf("g. maximum number of bytes allowed: %ld\n", mqds.msg_qbytes);
    printf("h. pid of the msgsnd: %d, msgrcv: %d\n", mqds.msg_lspid, mqds.msg_lrpid);
    
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