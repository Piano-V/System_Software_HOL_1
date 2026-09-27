#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Executing ls -Rl using execl...\n");
    execl("bin/ls", "ls", "-Rl", (char *)NULL);
    perror("execl failed");
    return 1;
}

