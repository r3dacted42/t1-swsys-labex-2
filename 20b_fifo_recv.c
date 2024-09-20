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
    int fd = open("./20.fifo", O_RDONLY);
    if (fd < 0) {
        perror("open failed with: ");
        return -1;
    }
    char buf[128];
    read(fd, buf, 128);
    printf("read from pipe: %s\n", buf);
    close(fd);

    return 0;
}

/* Check 20_fifo_one_way.sh for Sample Execution */