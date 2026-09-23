#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("[PID %d] Executing 'ls -Rl' using execl()...\n\n", getpid());
    fflush(stdout);

    // execl: Takes path to binary and list of arguments terminated by NULL
    execl("/bin/ls", "ls", "-Rl", (char *)NULL);

    perror("execl failed");
    return 1;
}

