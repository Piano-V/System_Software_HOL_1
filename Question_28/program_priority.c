#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    int prio = getpriority(PRIO_PROCESS, 0);
    printf("Current priority (nice value): %d\n", prio);

    nice(5);

    prio = getpriority(PRIO_PROCESS, 0);
    printf("New priority after nice(5): %d\n", prio);

    return 0;
}
