#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Executing ls -Rl using execlp...\n");
    execlp("ls", "ls", "-Rl", (char *)NULL);
    perror("execlp failed");
    return 1;
}
