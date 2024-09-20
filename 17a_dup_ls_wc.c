/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

17. Write a program to execute ls -l | wc.
    a. use dup <---
    b. use dup2
    c. use fcntl
========================================================================================
*/

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int fd[2];
    pipe(fd);
    int wr_fd = fd[1], rd_fd = fd[0];
    if (!fork()) {
        // wc
        close(wr_fd);
        close(STDIN_FILENO); // close STDIN
        dup(rd_fd); // copy read end of pipe to STDIN's fd number
        execl("/bin/wc", "wc", NULL);
    }
    // ls -l
    close(rd_fd);
    close(STDOUT_FILENO); // close STDOUT
    dup(wr_fd); // copy write end of pipe to STDOUT's fd number
    execl("/bin/ls", "ls", "-l", NULL);
}

/*
Sample Execution:

$ runc 17a_dup_ls_wc.c 
     34     299    2394

*/