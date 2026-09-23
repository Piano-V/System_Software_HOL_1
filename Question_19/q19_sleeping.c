#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Sleeping process started. PID: %d\n", getpid());
    fflush(stdout);

    // Puts process into sleep ('S' state)
    while (1) {
        sleep(60);
    }

    return 0;
}
/*
./q19_sleeping &
# Note the PID, e.g., 2102
ps -o pid,stat,comm -p 2102
*/