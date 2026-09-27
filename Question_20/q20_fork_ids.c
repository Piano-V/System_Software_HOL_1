#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Original process starting with PID: %d\n\n", getpid());

    pid_t pid = fork();

    if (pid == 0) {
        // Inside Child Process
        printf("I am the child process.\n");
        printf("My PID  (getpid()):  %d\n", getpid());
        printf("My PPID (getppid()): %d\n\n", getppid());
    } else {
        // Inside Parent process
        // sleep(5);
        printf("I am the parent process.\n");
        printf("My PID (getpid()):        %d\n", getpid());
        printf("Created Child PID (fork): %d\n\n", pid);

        wait(NULL);
    }

    return 0;
}