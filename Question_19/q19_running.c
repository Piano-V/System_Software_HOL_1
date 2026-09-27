#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Running process started. PID: %d\n", getpid());
    fflush(stdout);

    volatile unsigned long counter = 0;
    while (1) {
        counter++;
    }

    return 0;
}
/*
./q19_running &
ps -o pid,stat,comm -p pid
*/