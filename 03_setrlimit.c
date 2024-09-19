/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

3. Write a program to set (any one) system resource limit. Use setrlimit system call.
========================================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    printf("attempting to set RLIMIT_FSIZE to 16 bytes...\n");
    struct rlimit lim;
    lim.rlim_cur = 16;
    if (setrlimit(RLIMIT_FSIZE, &lim) < 0) {
        perror("setrlimit failed with: ");
        return -1;
    }
    printf("max file size that can be created with this process set to 16 bytes\n");

    char msg[] = "some random text intended to break the file size limit";
    printf("trying to write %lu bytes...\n", sizeof(msg) / sizeof(char));
    int fd = open("temp.txt", O_CREAT | O_WRONLY, 0666);
    int wr = write(fd, msg, sizeof(msg) / sizeof(char));
    printf("wrote %d bytes to file temp.txt\n", wr);
    close(fd);
    
    return 0;
}

/*
Sample Execution:

$ runc 03_setrlimit.c 
attempting to set RLIMIT_FSIZE to 16 bytes...
max file size that can be created with this process set to 16 bytes
trying to write 55 bytes...
wrote 16 bytes to file temp.txt

$ cat temp.txt
some random text

*/