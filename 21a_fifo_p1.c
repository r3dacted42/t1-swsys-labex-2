/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

21. Write two programs so that both can communicate by FIFO -Use two way communications.
========================================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    if (mknod("./21.fifo", 0666 | __S_IFIFO, 0) < 0) {
        perror("mknod failed with: ");
        return -1;
    }
    int fd = open("./21.fifo", O_WRONLY);
    printf("created and opened FIFO pipe ./21.fifo, will write a message...\n");
    char msg[] = "message from 21a";
    int wr = write(fd, msg, sizeof(msg) / sizeof(char));
    printf("wrote %d bytes to pipe\n", wr);
    close(fd);
    fd = open("./21.fifo", O_RDONLY);
    char buf[128];
    int rd = read(fd, buf, sizeof(buf) / sizeof(char));
    printf("read %d bytes from pipe: %s\n", rd, buf);
    close(fd);

    return 0;
}

/* Check 21_fifo_two_way.sh for Sample Execution */