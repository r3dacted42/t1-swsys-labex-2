/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

22. Write a program to wait for data to be written into FIFO within 10 seconds, use 
select system call with FIFO.
========================================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <time.h>

int main() {
    if (mknod("./22.fifo", 0666 | __S_IFIFO, 0) < 0) {
        perror("mknod failed with: ");
        return -1;
    }
    printf("FIFO pipe created\nopening pipe in read mode...\nopen ./22.fifo in write mode and send a message\n");
    int fd = open("./22.fifo", O_RDWR);
    fd_set set;
    FD_ZERO(&set);
    FD_SET(fd, &set);
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    int result = select(fd + 1, &set, NULL, NULL, &timeout);
    if (result) {
        char buf[128];
        int rd = read(fd, buf, sizeof(buf) / sizeof(char));
        printf("data found within 10 seconds! read %d bytes: %s", rd, buf);
    } else {
        printf("data not found within 10 seconds\n");
    }

    close(fd);
    unlink("./22.fifo");
    return 0;
}

/*
Sample Execution:

$ runc 22_fifo_select.c 
FIFO pipe created
opening pipe in read mode...
open ./22.fifo in write mode and send a message
data found within 10 seconds! read 12 bytes: hello there!

*/