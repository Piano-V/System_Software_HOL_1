#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int sleep_times[3] = {5, 7, 4};

    printf("[PARENT] PID: %d. Creating 3 child processes\n\n", getpid());

    for (int i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork failed");
            return 1;
        } else if (pids[i] == 0) {
            // Inside child process
            int child_num = i + 1;
            printf("[CHILD %d] PID: %d | Working for %d seconds\n", child_num, getpid(), sleep_times[i]);
            sleep(sleep_times[i]);
            printf("[CHILD %d] Finished work. Exiting.\n", child_num);
            exit(0);
        }
    }

    pid_t target_pid = pids[1]; // Child 2
    printf("Waiting for child 2\n");

    waitpid(target_pid, NULL, 0);
    printf("Child 2 has finished\n");

    // Clean up remaining children to avoid zombies
    while (wait(NULL) > 0);
    printf("Parent ends after reaping all children\n");

    return 0;
}
