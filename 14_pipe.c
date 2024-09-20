/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

14. Write a simple program to create a pipe, write to the pipe, read from pipe and 
display on the monitor.
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pipe(fd);
    int rd_fd = fd[0], wr_fd = fd[1];
    char buf[128];
    sprintf(buf, "some text that i wrote to the pipe");
    int wr = write(wr_fd, buf, sizeof(buf));
    printf("wrote %d bytes to pipe\n", wr);
    int rd = read(rd_fd, buf, sizeof(buf));
    printf("read %d bytes from the pipe:\n%s\n", rd, buf);
    close(rd_fd);
    close(wr_fd);

    return 0;
}

/*
Sample Execution:

$ runc 14_pipe.c 
wrote 128 bytes to pipe
read 128 bytes from the pipe:
some text that i wrote to the pipe

*/