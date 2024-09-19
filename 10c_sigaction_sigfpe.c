/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

10. Write a separate program using sigaction system call to catch the following signals.
    a. SIGSEGV
    b. SIGINT
    c. SIGFPE <---
========================================================================================
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "sig_handler.h"

// #define _POSIX_C_SOURCE 199309L

int main(int argc, char** argv) {
    struct sigaction action;
    action.sa_handler = handler;
    sigaction(SIGFPE, &action, NULL);
    float f = 1 / (argc - 1);

    return 0;
}

/*
Sample Execution:

$ runc 10c_sigaction_sigfpe.c 
signal of type SIGFPE received!!!

*/