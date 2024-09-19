/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       19 September 2024

7. Write a simple program to print the created thread ids.
========================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

struct thread_args {
    pthread_t thread_id;
};

void* thread_routine(void *args) {
    sleep(1);
    printf("exiting thread id %ld at %ld\n", ((struct thread_args*)args)->thread_id, clock());
    free(args);
    return NULL;
}

int main() {
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        struct thread_args *args = malloc(sizeof(*args));
        pthread_create(&threads[i], NULL, thread_routine, (void *)(args));
        printf("started thread %ld at %ld\n", threads[i], clock());
        args->thread_id = threads[i];
    }
    for (int i = 0; i < 3; i++) pthread_join(threads[i], NULL);

    return 0;
}

/*
Sample Execution:

$ gcc -pthread 07_print_thread_id.c && ./a.out
started thread 140140811163200 at 747
started thread 140140802770496 at 966
started thread 140140794377792 at 1061
exiting thread id 140140811163200 at 1179
exiting thread id 140140802770496 at 1186
exiting thread id 140140794377792 at 1373

*/