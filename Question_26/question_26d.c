#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("[PID %d] Executing 'ls -Rl' using execv()...\n\n", getpid());
    fflush(stdout);

    // Argument vector (array of strings) terminated by NULL
    char *const args[] = { "ls", "-Rl", NULL };

    // execv: Takes path to binary and argument vector
    execv("/bin/ls", args);

    // If execv is successful, this code is never reached
    perror("execv failed");
    return 1;
}
