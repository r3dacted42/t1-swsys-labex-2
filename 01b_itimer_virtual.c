/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       12 September 2024

1. Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
    a. ITIMER_REAL
    b. ITIMER_VIRTUAL <---
    c. ITIMER_PROF
========================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "01_handler.h"

int main(void) {
    signal(SIGVTALRM, handler);
    struct itimerval timer;
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    printf("waiting for signal...\n");
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) < 0) {
        perror("setitimer failed with: ");
        return -1;
    }
    while(1);
    return 0;
}

/*
Sample Execution:

$ runc 01b_itimer_virtual.c 
waiting for signal...
((after about 10 seconds))
signal of type SIGVTALRM received!!!

*/