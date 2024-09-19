/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

8. Write a separate program using signal system call to catch the following signals.
    a. SIGSEGV
    b. SIGINT
    c. SIGFPE
    d. SIGALRM (use alarm system call)
    e. SIGALRM (use setitimer system call)
    f. SIGVTALRM (use setitimer system call)
    g. SIGPROF (use setitimer system call) <---
========================================================================================
*/

#include <signal.h>
#include "sig_handler.h"
#include <unistd.h>

int main(int argc, char** argv) {
    signal(SIGPROF, handler);
    struct itimerval timer;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 1;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_PROF, &timer, NULL) < 0) {
        perror("setitimer failed with: ");
        return -1;
    }
    while(1);

    return 0;
}

/*
Sample Execution:

$ runc 08g_sigprof.c 
((after ~1 second))
signal of type SIGPROF received!!!

*/