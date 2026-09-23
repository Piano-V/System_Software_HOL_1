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
        printf("[CHILD]  I am the child process.\n");
        printf("[CHILD]  My PID  (getpid()):  %d\n", getpid());
        printf("[CHILD]  My PPID (getppid()): %d\n\n", getppid());
    } else {
        // Inside Parent process
        // sleep(5);
        printf("[PARENT] I am the parent process.\n");
        printf("[PARENT] My PID (getpid()):        %d\n", getpid());
        printf("[PARENT] Created Child PID (fork): %d\n\n", pid);

        // Wait for the child process to finish to avoid leaving a zombie
        wait(NULL);
    }

    return 0;
}