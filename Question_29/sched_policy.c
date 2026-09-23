#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>

void show_policy() {
    int policy = sched_getscheduler(0); // 0 refers to the calling process

    if (policy == SCHED_OTHER)
        printf("Current Policy: SCHED_OTHER (Standard)\n");
    else if (policy == SCHED_FIFO)
        printf("Current Policy: SCHED_FIFO (Real-Time FIFO)\n");
    else if (policy == SCHED_RR)
        printf("Current Policy: SCHED_RR (Real-Time Round Robin)\n");
    else
        perror("sched_getscheduler failed");
}

int main() {
    // get initial policy
    printf("Initial State \n");
    show_policy();

    // set policy to SCHED_FIFO (requires priority between 1 and 99)
    struct sched_param param;
    param.sched_priority = 10;

    printf("\n Changing to SCHED_FIFO \n");
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("Error setting SCHED_FIFO \n");
    } else {
        printf("Successfully updated!\n");
    }
    show_policy();

    // revert back to default SCHED_OTHER (priority must be 0)
    param.sched_priority = 0;

    printf("\n--- Reverting to SCHED_OTHER ---\n");
    if (sched_setscheduler(0, SCHED_OTHER, &param) == -1) {
        perror("Error reverting to SCHED_OTHER");
    } else {
        printf("Successfully reverted!\n");
    }
    show_policy();

    return 0;
}