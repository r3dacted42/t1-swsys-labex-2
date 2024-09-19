/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

9. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
========================================================================================
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    signal(SIGINT, SIG_IGN);
    printf("pressing Ctrl+C for the next 5 seconds will do nothing...\n");
    sleep(5);
    printf("\npress Ctrl+C again to exit program...\n");
    signal(SIGINT, SIG_DFL);
    while(1);

    return 0;
}

/*
Sample Execution:

$ runc 09_sigint_ignore.c 
pressing Ctrl+C for the next 5 seconds will do nothing...
^C^C^C^C^C^C
press Ctrl+C again to exit program...
^C

*/