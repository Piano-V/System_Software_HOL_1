#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child PID: %d, Initial PPID: %d\n", getpid(), getppid());
        printf("Child sleeping for 5 seconds...\n");
        sleep(5);
        printf("Child woke up. New PPID after adoption: %d\n", getppid());
        exit(0);
    } else {
        printf("Parent PID: %d created child PID: %d. Exiting parent.\n", getpid(), pid);
        exit(0);
    }

    return 0;
}