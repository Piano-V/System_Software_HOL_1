#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>

void show_policy() {
    int policy = sched_getscheduler(0); // 0 refers to the calling process

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
    // get initial policy
    printf("Initial State \n");
    show_policy();

    // set policy to SCHED_FIFO (requires priority between 1 and 99)
    struct sched_param param;
    param.sched_priority = 10;

    printf("\n Changing to SCHED_FIFO \n");
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("Error\n");
    } else {
        printf("Successfully updated\n");
    }
    show_policy();

    // revert back to default SCHED_OTHER (priority must be 0)
    param.sched_priority = 0;

    printf("\n Changing back to SCHED_OTHER ---\n");
    if (sched_setscheduler(0, SCHED_OTHER, &param) == -1) {
        perror("Error");
    } else {
        printf("Done\n");
    }
    show_policy();

    return 0;
}