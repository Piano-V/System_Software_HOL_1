#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child Process
        printf("[CHILD]  Started. PID: %d | Initial Parent PPID: %d\n", getpid(), getppid());
        
        printf("[CHILD]  Sleeping for 5 seconds waiting for parent to exit\n");
        sleep(5);

        // After the parent dies the PPID changes of the child
        printf("[CHILD]  Woke up. Current PPID after adoption: %d\n", getppid());
        printf("[CHILD]  Child process end\n");
        exit(0);
    } else {
        // Parent Process
        printf("[PARENT] Started. PID: %d | Created Child PID: %d\n", getpid(), pid);
        printf("[PARENT] Exit so child becomes an orphan\n");
        exit(0);
    }

    return 0;
}