#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child Process
        printf("[CHILD]  PID: %d | Exiting immediately to become a zombie...\n", getpid());
        exit(0);
    } else {
        // Parent Process
        printf("[PARENT] PID: %d | Created child PID: %d\n", getpid(), pid);
        printf("[PARENT] Sleeping for 25 seconds WITHOUT calling wait()...\n");
        printf("[PARENT] Check the child state in another terminal now\n\n");

        // Sleeping keeps the parent alive without reaping the child
        sleep(25);

        printf("[PARENT] Woke up! Exiting now. Child will be cleaned up by PID 1.\n");
    }

    return 0;
}
/*
In other terminal:
ps -o pid,ppid,stat,comm -p <pid>
*/