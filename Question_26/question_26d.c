#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *const args[] = { "ls", "-Rl", NULL };

    printf("Executing ls -Rl using execv...\n");
    execv("/bin/ls", args);
    perror("execv failed");
    return 1;
}
