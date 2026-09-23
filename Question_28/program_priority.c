#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

void print_current_priority() {
    errno = 0;
    int prio = getpriority(PRIO_PROCESS, 0); // 0 means current process

    if (prio == -1 && errno != 0) {
        perror("getpriority failed");
        exit(EXIT_FAILURE);
    }

    printf("[PID: %d] Current nice value: %d\n", getpid(), prio);
}

int main(int argc, char *argv[]) {
    int increment = 5;
    if (argc > 1) {
        increment = atoi(argv[1]);
    }

    printf("Inspecting Initial Priority \n");
    print_current_priority();

    printf("\n Modifying Priority with nice(%d) \n", increment);
    errno = 0;
    int ret = nice(increment);

    if (ret == -1 && errno != 0) {
        perror("nice() failed");
    } else {
        printf("nice() system call succeeded.\n");
    }

    printf("\n Priority After Modification \n");
    print_current_priority();

    return 0;
}