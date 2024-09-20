/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

16. Write a program to send and receive data from parent to child vice versa. Use two 
way communication.
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];
    pipe(fd1); // parent to child
    pipe(fd2); // child to parent
    int rd_fd_c = fd1[0], wr_fd_p = fd1[1], rd_fd_p = fd2[0], wr_fd_c = fd2[1];
    char buf[128];
    if (!fork()) {
        // child
        close(wr_fd_p); // close write end of parent's pipe
        close(rd_fd_p); // close read end of child's pipe
        int rd = read(rd_fd_c, buf, sizeof(buf));
        printf("[%6d c] read %d bytes from pipe: %s\n", getpid(), rd, buf);
        sprintf(buf, "message for my creator :D");
        int wr = write(wr_fd_c, buf, sizeof(buf));
        printf("[%6d c] wrote %d bytes to pipe\n", getpid(), wr);        
        close(rd_fd_c);
        close(wr_fd_c);
        return 0;
    }
    close(wr_fd_c); // close write end of child's pipe
    close(rd_fd_c); // close read end of parent's pipe
    sprintf(buf, "message for my spawn :)");
    int wr = write(wr_fd_p, buf, sizeof(buf));
    printf("[%6d p] wrote %d bytes to pipe\n", getpid(), wr);
    int rd = read(rd_fd_p, buf, sizeof(buf));
    printf("[%6d p] read %d bytes from pipe: %s\n", getpid(), rd, buf);
    wait(NULL);
    close(wr_fd_p);
    close(rd_fd_p);

    return 0;
}

/*
Sample Execution:

$ runc 16_vice_versa.c 
[ 22209 p] wrote 128 bytes to pipe
[ 22210 c] read 128 bytes from pipe: message for my spawn :)
[ 22210 c] wrote 128 bytes to pipe
[ 22209 p] read 128 bytes from pipe: message for my creator :D

*/