#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int sleep_times[3] = {2, 6, 4};

    printf("[PARENT] PID: %d. Spawning 3 child processes...\n\n", getpid());

    // Fork 3 child processes
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork failed");
            return 1;
        } else if (pids[i] == 0) {
            // Inside child process
            int child_num = i + 1;
            printf("[CHILD %d] PID: %d | Working for %d seconds\n",  child_num, getpid(), sleep_times[i]);
            
            sleep(sleep_times[i]);

            printf("[CHILD %d] PID: %d | Finished work. Exiting with code %d\n", child_num, getpid(), child_num * 10);
            exit(child_num * 10);
        }
    }

    // Parent execution continues here
    pid_t target_pid = pids[1];
    int status;

    printf("[PARENT] Waiting for Child 2 (PID %d) using waitpid()\n", target_pid);

    // Block specifically for Child 2
    pid_t reaped_pid = waitpid(target_pid, &status, 0);

    if (reaped_pid == -1) {
        perror("waitpid error");
        return 1;
    }

    if (WIFEXITED(status)) {
        printf("\n[PARENT] Successfully reaped TARGET Child (PID %d) with exit status: %d\n\n", reaped_pid, WEXITSTATUS(status));
    }

    // Clean up remaining children to avoid leaving zombies
    printf("[PARENT] Cleaning up remaining children...\n");
    while ((reaped_pid = wait(NULL)) > 0) {
        printf("[PARENT] Reaped remaining child PID %d\n", reaped_pid);
    }

    printf("[PARENT] All children handled. Exiting.\n");
    return 0;
}