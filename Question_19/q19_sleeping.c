#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Sleeping process started. PID: %d\n", getpid());
    fflush(stdout);

    while (1) {
        sleep(60);
    }

    return 0;
}
/*
./q19_sleeping &
ps -o pid,stat,comm -p pid
*/