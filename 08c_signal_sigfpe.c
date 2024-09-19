/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

8. Write a separate program using signal system call to catch the following signals.
    a. SIGSEGV
    b. SIGINT
    c. SIGFPE <---
    d. SIGALRM (use alarm system call)
    e. SIGALRM (use setitimer system call)
    f. SIGVTALRM (use setitimer system call)
    g. SIGPROF (use setitimer system call)
========================================================================================
*/

#include <signal.h>
#include "sig_handler.h"

int main(int argc, char** argv) {
    signal(SIGFPE, handler);
    float f = 1 / (argc - 1);

    return 0;
}

/*
Sample Execution:

$ runc 08c_floating_point_err.c 
signal of type SIGFPE received!!!

*/