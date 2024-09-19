/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

12. Write a program to create an orphan process. Use kill system call to send SIGKILL 
signal to the parent process from the child process.
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    if (!fork()) {
        // kiddo
        printf("[%6d c] will try to kill my parent to get a new one >:)\n", getpid());
        sleep(1);
        kill(getppid(), SIGKILL);
        sleep(1);
        printf("\n[%6d c] killed parent successfully!\n", getpid());
        printf("[%6d c] new parent: %6d\n", getpid(), getppid());
        return 0;
    }
    printf("[%6d p] waiting to be murdered by my own spawn :D\n", getpid());
    wait(NULL);

    return 0;
}

/*
Sample Execution:

$ ./12.o
[174527 p] waiting to be murdered by my own spawn :D
[174528 c] will try to kill my parent to get a new one >:)
((after 1 second))
Killed
$ 
((after 1 second))
[174528 c] killed parent successfully!
[174528 c] new parent:  28915

*/