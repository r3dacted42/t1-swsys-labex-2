/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       20 September 2024

19. Create a FIFO file by
    a. mknod command
    b. mkfifo command
    c. use strace command to find out, which command (mknod or mkfifo) is better.
    c. mknod system call <---
    d. mkfifo library function
========================================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    if (mknod("./19c.fifo", 0666 | __S_IFIFO, 0) < 0) {
        perror("mknod failed with: ");
        return -1;
    }
    printf("open ./19c.fifo in read mode and press enter to continue...\n");
    getchar();
    int fifo_fd = open("./19c.fifo", O_WRONLY);
    char msg[] = "hello there, this was written to the fifo pipe!\n";
    int count = write(fifo_fd, msg, sizeof(msg)/sizeof(char));
    close(fifo_fd);
    printf("%d characters written to pipe\n", count);
    return 0;
}

/*
Sample Execution:

$ runc 19c_mknod_make_pipe.c
open ./19c.fifo in read mode and press enter to continue...

--on another terminal instance:
$ cat 19c.fifo
hello there, this was written to the fifo pipe!

--on previous terminal:
49 characters written to pipe

$ ll
...
prw-r--r-- 1 r3dacted42 r3dacted42     0 Sep 20 16:12 19c.fifo|
...

*/