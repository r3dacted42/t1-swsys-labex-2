/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

13. Write two programs: first program is waiting to catch SIGSTOP signal, <---
the second program will send the signal (using kill system call). Find out whether the 
first program is able to catch the signal or not.
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "sig_handler.h"

int main() {
    signal(SIGSTOP, handler);
    printf("[%6d P1] waiting for SIGSTOP...\n", getpid());
    while (1);

    return 0;
}

/*
Check 13_check.sh for Sample Execution.

*/