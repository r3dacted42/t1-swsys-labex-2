/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       21 September 2024

29. Write a program to remove the message queue.
========================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int mqid = -1;
    if (argc == 2) {
        mqid = 0;
        for (int i = 0; argv[1][i] != 0; i++) mqid = mqid * 10 + (argv[1][i] - 48);
        printf("will try to remove message queue with id: %d\n", mqid);
    } else {
        printf("please provide the id of the queue to remove!\n");
        printf("usage: %s <mq-id>\n", argv[0]);
        return -1;
    }
    if (!msgctl(mqid, IPC_RMID, NULL)) {
        printf("successfully removed msg queue [id: %d]\n", mqid);
    } else {
        perror("msgctl failed with: ");
        return -1;
    }
    
    return 0;
}

/*
Sample Execution:

-- no args
$ runc 29_msg_q_rm.c 
please provide the id of the queue to remove!
usage: ./run-1726903917.o <mq-id>

-- msg queue id given
$ runc 29_msg_q_rm.c 3
will try to remove message queue with id: 3
successfully removed msg queue [id: 3]

$ ipcs --q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages

*/