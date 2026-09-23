#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = getpid();
    printf("Process running with PID: %d\n", pid);
    printf("Inspect open FDs using: ls -l /proc/%d/fd\n", pid);
    fflush(stdout);

    int file_count = 0;
    char filename[64];

    while (1) {
        // Generate 5 new files per loop iteration
        for (int i = 0; i < 5; i++) {
            snprintf(filename, sizeof(filename), "dummy_file_%d.txt", file_count++);
            
            int fd = creat(filename, 0644);
            printf("Opened %s with FD: %d\n", filename, fd);
        }

        // Sleep to give time to inspect /proc/<pid>/fd in another command
        sleep(5);
    }

    return 0;
}