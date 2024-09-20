/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

18. Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
========================================================================================
*/

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int fd1[2];
    pipe(fd1);
    int ls_grep_rd = fd1[0], ls_grep_wr = fd1[1];
    if (!fork()) {
        int fd2[2];
        pipe(fd2);
        int grep_wc_rd = fd2[0], grep_wc_wr = fd2[1];
        close(ls_grep_wr);
        if (!fork()) {
            // wc
            close(grep_wc_wr);
            dup2(grep_wc_rd, STDIN_FILENO);
            execl("/bin/wc", "wc", NULL);
        }
        // grep ^d
        dup2(ls_grep_rd, STDIN_FILENO);
        close(grep_wc_rd);
        dup2(grep_wc_wr, STDOUT_FILENO);
        execl("/bin/grep", "grep", "^d", NULL);
    }
    // ls -l
    close(ls_grep_rd);
    dup2(ls_grep_wr, STDOUT_FILENO);
    execl("/bin/ls", "ls", "-l", NULL);
}

/*
Sample Execution:

$ runc 18_count_dirs.c 
      0       0       0

*/