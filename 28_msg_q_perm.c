/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

28. Write a program to change the existing message queue permission. 
(use msqid_ds structure)
========================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t key = ftok(".", 'a');
    int mqid = msgget(key, IPC_CREAT | 0666);
    printf("msg queue key: %d, id: %d\n", key, mqid);
    struct msqid_ds mqds;
    msgctl(mqid, IPC_STAT, &mqds);
    mqds.msg_perm.mode = 0765;
    if (!msgctl(mqid, IPC_SET, &mqds)) {
        printf("successfully modified msg queue, permissions set to 0765\n");
    } else {
        perror("msgctl failed with: ");
        return -1;
    }
    
    return system("ipcs --q");
}

/*
Sample Execution:

$ runc 28_msg_q_exit.c 
msg queue key: 1629509924, id: 3
successfully modified msg queue, permissions set to 0765

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x61205924 3          r3dacted42 765        0            0

*/