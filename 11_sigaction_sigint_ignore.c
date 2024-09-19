/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

11. Write a program to ignore a SIGINT signal then reset the default action of the 
SIGINT signal - use sigaction system call.
========================================================================================
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "sig_handler.h"

// #define _POSIX_C_SOURCE 199309L

int main() {
    struct sigaction action;
    action.sa_handler = SIG_IGN;
    sigaction(SIGINT, &action, NULL);
    printf("pressing Ctrl+C will have no effect for the next 5 seconds...\n");
    sleep(5);
    action.sa_handler = SIG_DFL;
    sigaction(SIGINT, &action, NULL);
    printf("\npress Ctrl+C again to exit...\n");
    while(1);

    return 0;
}

/*
Sample Execution:

$ runc 11_sigaction_sigint_ignore.c 
pressing Ctrl+C will have no effect for the next 5 seconds...
^C^C^C^C^C^C^C
press Ctrl+C again to exit...
^C

*/