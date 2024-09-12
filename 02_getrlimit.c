/*
========================================================================================
Name:       Priyansh Agrahari
Reg. No.:   MT2024120
Date:       12 September 2024

2. Write a program to print the system resource limits. Use getrlimit system call.
========================================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

int get_lim(int idx, char *name, char *desc) {
    switch (idx) {
        case 0: sprintf(name, "%s", "RLIMIT_AS");
        sprintf(desc, "%s", "maximum size of the process's virtual memory (address space)"); 
        return RLIMIT_AS;
        case 1: sprintf(name, "%s", "RLIMIT_CORE");
        sprintf(desc, "%s", "maximum size of core file that can be created, in bytes"); 
        return RLIMIT_CORE;
        case 2: sprintf(name, "%s", "RLIMIT_CPU");
        sprintf(desc, "%s", "per-process CPU limit in seconds"); 
        return RLIMIT_CPU;
        case 3: sprintf(name, "%s", "RLIMIT_DATA");
        sprintf(desc, "%s", "maximum size of data segment, in bytes"); 
        return RLIMIT_DATA;
        case 4: sprintf(name, "%s", "RLIMIT_FSIZE");
        sprintf(desc, "%s", "maximum size of a regular file that can be created, in bytes"); 
        return RLIMIT_FSIZE;
        case 5: sprintf(name, "%s", "RLIMIT_NICE");
        sprintf(desc, "%s", "ceiling  to  which  the  process's nice value can be raised"); 
        return RLIMIT_NICE;
    }
    return -1;
}



int main() {
    char *name = calloc(sizeof(char), 16), *desc = calloc(sizeof(char), 84);
    memset(name, '\0', 16); memset(desc, '\0', 84);
    struct rlimit rlim;
    printf("+-----------------+--------+--------+-------------------------------------------------------------------------------------+\n");
    printf("|      NAME       |  SOFT  |  HARD  |                                    DESCRIPTION                                      |\n");
    printf("|-----------------+--------+--------+-------------------------------------------------------------------------------------|\n");
    for (int i = 0, lim; i < 6; i++) {
        if ((lim = get_lim(i, name, desc)) >= 0) {
            getrlimit(lim, &rlim);
            printf("| %-15s |", name);
            if (rlim.rlim_cur == RLIM_INFINITY) printf("    INF |"); else printf(" %6ld |", rlim.rlim_cur);
            if (rlim.rlim_max == RLIM_INFINITY) printf("    INF |"); else printf(" %6ld |", rlim.rlim_max);
            printf(" %-83s |\n", desc);
        }
    }
    printf("+-----------------+--------+--------+-------------------------------------------------------------------------------------+\n");
    return 0;
}

/*
Sample Execution:

$ runc 02_getrlimit.c 
+-----------------+--------+--------+-------------------------------------------------------------------------------------+
|      NAME       |  SOFT  |  HARD  |                                    DESCRIPTION                                      |
|-----------------+--------+--------+-------------------------------------------------------------------------------------|
| RLIMIT_AS       |    INF |    INF | maximum size of the process's virtual memory (address space)                        |
| RLIMIT_CORE     |      0 |    INF | maximum size of core file that can be created, in bytes                             |
| RLIMIT_CPU      |    INF |    INF | per-process CPU limit in seconds                                                    |
| RLIMIT_DATA     |    INF |    INF | maximum size of data segment, in bytes                                              |
| RLIMIT_FSIZE    |    INF |    INF | maximum size of a regular file that can be created, in bytes                        |
| RLIMIT_NICE     |      0 |      0 | ceiling  to  which  the  process's nice value can be raised                         |
+-----------------+--------+--------+-------------------------------------------------------------------------------------+

*/