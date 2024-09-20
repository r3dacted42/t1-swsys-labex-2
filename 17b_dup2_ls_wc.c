/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

17. Write a program to execute ls -l | wc.
    a. use dup
    b. use dup2 <---
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
        dup2(rd_fd, STDIN_FILENO); // replace read end of pipe with STDIN's fd number
        execl("/bin/wc", "wc", NULL);
    }
    // ls -l
    close(rd_fd);
    dup2(wr_fd, STDOUT_FILENO); // replace write end of pipe with STDOUT's fd number
    execl("/bin/ls", "ls", "-l", NULL);
}

/*
Sample Execution:

$ runc 17b_dup2_ls_wc.c 
     35     308    2465

*/