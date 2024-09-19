/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

13. Write two programs: first program is waiting to catch SIGSTOP signal,
the second program will send the signal (using kill system call). Find out whether the 
first program is able to catch the signal or not. <---
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "sig_handler.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("must provide pid as cmd line arg.\n");
        return -1;
    }
    pid_t pid = 0;
    for (int i = 0; argv[1][i] != 0; i++) {
        pid = (pid * 10 + argv[1][i] - 48);
    }
    printf("[%6d P2] received pid: %6d\n", getpid(), pid);
    kill(pid, SIGSTOP);
    printf("[%6d P2] SIGSTOP sent to %6d, exiting...\n", getpid(), pid);

    return 0;
}

/*
Check 13_check.sh for Sample Execution.

*/