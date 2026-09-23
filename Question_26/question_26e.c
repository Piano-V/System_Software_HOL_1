#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("[PID %d] Executing 'ls -Rl' using execvp()...\n\n", getpid());
    fflush(stdout);

    // Argument vector (array of strings) terminated by NULL
    char *const args[] = { "ls", "-Rl", NULL };

    // execvp: Resolves executable name using PATH and takes argument vector
    execvp("ls", args);

    // If execvp is successful, this code is never reached
    perror("execvp failed");
    return 1;
}