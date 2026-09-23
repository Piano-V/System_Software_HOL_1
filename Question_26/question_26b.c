#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("[PID %d] Executing 'ls -Rl' using execlp()...\n\n", getpid());
    fflush(stdout);

    // execlp: Resolves executable name using PATH and takes list of arguments terminated by NULL
    execlp("ls", "ls", "-Rl", (char *)NULL);

    // If execlp is successful, this code is never reached
    perror("execlp failed");
    return 1;
}
