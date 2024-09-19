#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

char* signal_to_name(int signal, int *alloc_d) {
    switch (signal) {
        case SIGALRM: return "SIGALRM";
        case SIGVTALRM: return "SIGVTALRM";
        case SIGPROF: return "SIGPROF";
        case SIGSEGV: return "SIGSEGV";
        case SIGINT: return "SIGINT";
        case SIGFPE: return "SIGFPE";
        case SIGSTOP: return "SIGSTOP";
    }
    char* oth = (char*)calloc(sizeof(char), 16);
    *alloc_d = 1;
    sprintf(oth, "OTHER (%d)", signal);
    return oth;
}

void handler(int signal_type) {
    int alloc_d = 0;
    char *name = signal_to_name(signal_type, &alloc_d);
    printf("signal of type %s received!!!\n", name);
    if (alloc_d) free(name);
    exit(0);
}