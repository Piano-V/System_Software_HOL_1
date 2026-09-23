#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>

void display_priority_limits(const char *policy_name, int policy) {
    int max_prio = sched_get_priority_max(policy);
    int min_prio = sched_get_priority_min(policy);

    if (max_prio == -1 || min_prio == -1) {
        perror("sched_get_priority failed");
        return;
    }

    printf("%s | Min Priority: %d | Max Priority: %d\n", policy_name, min_prio, max_prio);
}

int main() {
    printf("Linux Scheduler Priority Ranges:\n");
    printf("\n");

    // Real time policies
    display_priority_limits("SCHED_FIFO", SCHED_FIFO);
    display_priority_limits("SCHED_RR", SCHED_RR);

    // Standard non real time policy
    display_priority_limits("SCHED_OTHER", SCHED_OTHER);

    return 0;
}