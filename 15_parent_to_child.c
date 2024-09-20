/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

15. Write a simple program to send some data from parent to the child process.
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);
    int rd_fd = fd[0], wr_fd = fd[1];
    char buf[128];
    if (!fork()) {
        // child
        close(wr_fd);
        int rd = read(rd_fd, buf, sizeof(buf));
        printf("[%6d c] read %d bytes from pipe: %s\n", getpid(), rd, buf);
        close(rd_fd);
        return 0;
    }
    close(rd_fd);
    sprintf(buf, "message for my spawn :)");
    int wr = write(wr_fd, buf, sizeof(buf));
    printf("[%6d p] wrote %d bytes to pipe\n", getpid(), wr);
    close(wr_fd);
    wait(NULL);

    return 0;
}

/*
Sample Execution:

$ runc 15_parent_to_child.c 
[ 17375 p] wrote 128 bytes to pipe
[ 17376 c] read 128 bytes from pipe: message for my spawn :)

*/