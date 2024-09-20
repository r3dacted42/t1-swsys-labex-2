/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

20. Write two programs so that both can communicate by FIFO -Use one way communication.
========================================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    if (mknod("./20.fifo", 0666 | __S_IFIFO, 0) < 0) {
        perror("mknod failed with: ");
        return -1;
    }
    int fd = open("./20.fifo", O_WRONLY);
    printf("created and opened FIFO pipe ./20.fifo, will write a message...\n");
    char msg[] = "message from 20a";
    int wr = write(fd, msg, sizeof(msg) / sizeof(char));
    printf("wrote %d bytes to pipe\n", wr);
    close(fd);

    return 0;
}

/* Check 20_fifo_one_way.sh for Sample Execution */