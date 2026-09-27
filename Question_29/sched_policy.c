#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>

void show_policy() {
    int policy = sched_getscheduler(0);

    if (policy == SCHED_OTHER)
        printf("Current Policy: SCHED_OTHER\n");
    else if (policy == SCHED_FIFO)
        printf("Current Policy: SCHED_FIFO \n");
    else if (policy == SCHED_RR)
        printf("Current Policy: SCHED_RR \n");
    else
        perror("failed");
}

int main() {
    printf("Initial State \n");
    show_policy();

    struct sched_param param;
    param.sched_priority = 10;

    printf("Changing to SCHED_FIFO \n");
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("Error");
    } else {
        printf("Successfully updated\n");
    }
    show_policy();

    param.sched_priority = 0;

    printf("Changing back to SCHED_OTHER \n");
    if (sched_setscheduler(0, SCHED_OTHER, &param) == -1) {
        perror("Error");
    } else {
        printf("Done\n");
    }
    show_policy();

    return 0;
}