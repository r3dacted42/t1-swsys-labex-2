/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

23. Write a program to print the maximum number of files can be opened within a process 
and size of a pipe (circular buffer).
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>

int main() {
    printf("maximum number of open files: %ld\n", sysconf(FOPEN_MAX));
    printf("size of pipe: %ld\n", pathconf(".", _PC_PIPE_BUF));

    return 0;
}

/*
Sample Execution:

$ runc 23_pipe_size.c 
maximum number of open files: 200809
size of pipe: 4096

*/