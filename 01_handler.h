#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

char* signal_to_name(int signal) {
    switch (signal) {
        case SIGALRM: return "SIGALRM";
        case SIGVTALRM: return "SIGVTALRM";
        case SIGPROF: return "SIGPROF";
    }
    char* oth = calloc(sizeof(char), 16);
    sprintf(oth, "OTHER (%d)", signal);
    return oth;
}

void handler(int signal_type) {
    printf("signal of type %s received!!!\n", signal_to_name(signal_type));
    exit(0);
}