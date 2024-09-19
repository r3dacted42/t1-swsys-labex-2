/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

10. Write a separate program using sigaction system call to catch the following signals.
    a. SIGSEGV <---
    b. SIGINT
    c. SIGFPE
========================================================================================
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "sig_handler.h"

// #define _POSIX_C_SOURCE 199309L

int main() {
    struct sigaction action;
    action.sa_handler = handler;
    sigaction(SIGSEGV, &action, NULL);
    (*(char*) NULL) = 0;

    return 0;
}

/*
Sample Execution:

$ runc 10a_sigaction_sigsegv.c 
signal of type SIGSEGV received!!!

*/