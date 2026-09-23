#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Running process started. PID: %d\n", getpid());
    fflush(stdout);

    // loop keeps the process in the Running state
    volatile unsigned long counter = 0;
    while (1) {
        counter++;
    }

    return 0;
}
/*
// Verify Running State:
// Inside Bash:
./q19_running &
// Note the PID, eg, 2101
ps -o pid,stat,comm -p 2101
*/