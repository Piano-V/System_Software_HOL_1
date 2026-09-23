#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
    printf("Process started. PID: %d\n", getpid());
    printf("Raising SIGSTOP to put itself into the STOPPED ('T') state...\n");
    fflush(stdout);

    // Send SIGSTOP signal to self
    raise(SIGSTOP);

    // This line only prints after receiving SIGCONT
    printf("Process resumed! PID: %d\n", getpid());
    while (1) {
        sleep(5);
    }

    return 0;
}
/*
./q19_stopped &
# Note the PID, eg, 2103
ps -o pid,stat,comm -p 2103

To Make the process come back to Running or Sleeping State:
kill -SIGCONT <pid>

Finally kill all processes:
killall -9 q19_running q19_sleeping q19_stopped
*/