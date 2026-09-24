#include <stdio.h>
#include <unistd.h>

int main() {
    // process ID to know which /proc entry to inspect
    pid_t pid = getpid();
    printf("Background process started with PID: %d\n", pid);
    fflush(stdout);

    while (1){
        sleep(5);
    }

    return 0;
}

//cat /proc/PID/status | head -n 15
//cat /proc/PID/cmdline
// ls -l /proc/12345/exe  executable path
// ls -l /proc/12345/cwd