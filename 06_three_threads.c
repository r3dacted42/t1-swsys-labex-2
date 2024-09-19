/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

6. Write a simple program to create three threads.
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

struct thread_args {
    int thread_idx;
};

void* thread_routine(void *args) {
    printf("inside thread %d at %ld\n", ((struct thread_args*)args)->thread_idx, clock());
    free(args);
    return NULL;
}

int main() {
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        struct thread_args *args = malloc(sizeof(*args));
        args->thread_idx = i;
        printf("starting thread %d at %ld\n", args->thread_idx, clock());
        pthread_create(&threads[i], NULL, thread_routine, (void *)(args));
    }
    for (int i = 0; i < 3; i++) pthread_join(threads[i], NULL);

    return 0;
}

/*
Sample Execution:

$ gcc -pthread 06_three_threads.c && ./a.out
starting thread 0 at 446
starting thread 1 at 510
starting thread 2 at 540
inside thread 0 at 600
inside thread 1 at 636
inside thread 2 at 788

*/