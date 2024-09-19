/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

5. Write a program to print the system limitation of
    a. maximum length of the arguments to the exec family of functions.
    b. maximum number of simultaneous process per user id.
    c. number of clock ticks (jiffy) per second.
    d. maximum number of open files
    e. size of a page
    f. total number of pages in the physical memory
    g. number of currently available pages in the physical memory.
========================================================================================

ref: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/limits.h.html
*/

#include <unistd.h>
#include <stdio.h>

int main() {
    printf("maximum length of the arguments to the exec family of functions: %ld\n", sysconf(_SC_ARG_MAX));
    printf("maximum number of simultaneous processes per real user id: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("number of clock ticks (jiffy) per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("maximum number of open files: %ld\n", sysconf(FOPEN_MAX));
    printf("size of a page: %ld\n", sysconf(_SC_PAGESIZE));
    printf("total number of pages in the physical memory: %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("number of currently available pages in the physical memory: %ld\n", sysconf(_SC_AVPHYS_PAGES));

    return 0;
}

/*
Sample Execution:

$ runc 05_other_lims.c 
maximum length of the arguments to the exec family of functions: 2097152
maximum number of simultaneous processes per real user id: 31437
number of clock ticks (jiffy) per second: 100
maximum number of open files: 200809
size of a page: 4096
total number of pages in the physical memory: 2013704
number of currently available pages in the physical memory: 1693860

*/