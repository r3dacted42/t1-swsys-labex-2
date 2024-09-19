/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

4. Write a program to measure how much time is taken to execute 100 getppid ( )
   system call. Use time stamp counter.
========================================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>
#include <unistd.h>

int main() {
    unsigned long long start = __rdtsc();
    for (int i = 0; i < 100; i++) getppid();
    unsigned long long end = __rdtsc();
    printf("time difference obtained by using the TSC register: %llu\n", end - start);

    return 0;
}

/*
Sample Execution:

$ runc 04_getppid_calls.c 
time difference obtained by using the TSC register: 23780

*/