#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child PID: %d exiting...\n", getpid());
        exit(0);
    } else {
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
        printf("Parent sleeping for 25 seconds...\n");
        sleep(25);
        printf("Parent exiting.\n");
    }

    return 0;
}