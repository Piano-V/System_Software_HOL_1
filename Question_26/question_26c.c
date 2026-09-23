#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("[PID %d] Executing 'ls -Rl' using execle()...\n\n", getpid());
    fflush(stdout);

    // Custom environment variables array passed to the new process
    char *const envp[] = { "PATH=/bin:/usr/bin", "TERM=xterm", NULL };

    // execle: Takes path to binary, list of arguments terminated by NULL, and an environment pointer
    execle("/bin/ls", "ls", "-Rl", (char *)NULL, envp);

    // If execle is successful, this code is never reached
    perror("execle failed");
    return 1;
}
