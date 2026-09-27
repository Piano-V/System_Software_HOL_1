#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char *const args[] = { "ls", "-Rl", NULL };

    printf("Executing ls -Rl using execvp...\n");
    execvp("ls", args);
    perror("execvp failed");
    return 1;
}